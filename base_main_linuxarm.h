/*
 * @Author: Flying
 * @Date: 2022-02-25 22:54:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-20 20:20:54
 * @Description: file content
 */
#include "lvgl/lvgl.h"
#include "my_drivers/display/fbdev.h"
#include "my_drivers/indev/evdev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <alloca.h>
#include "base_main.h"

#define DISP_BUF_SIZE (MY_UI_W_MAX * MY_UI_H_MAX)

#define EPOLL_LISTEN_CNT 256
#define EPOLL_LISTEN_TIMEOUT 500
static int g_epollfd = -1;
static int g_timerfd = -1;
static int epoll_add_fd(int fd)
{
    int ret;
    struct epoll_event event;

    memset(&event, 0, sizeof(event));
    event.data.fd = fd;
    event.events = EPOLLIN | EPOLLET;

    ret = epoll_ctl(g_epollfd, EPOLL_CTL_ADD, fd, &event);
    if (ret < 0)
    {
        return -1;
    }

    return 0;
}

static int epollfd_init()
{
    int epfd;

    /* create epoll fd */
    epfd = epoll_create(EPOLL_LISTEN_CNT);
    if (epfd < 0)
    {
        return -1;
    }
    g_epollfd = epfd;

    return epfd;
}
static int timerfd_init()
{
    int tmfd;
    int ret;
    struct itimerspec new_value;

    new_value.it_value.tv_sec = 0;
    new_value.it_value.tv_nsec = 10 * 1000 * 1000;
    new_value.it_interval.tv_sec = 0;
    new_value.it_interval.tv_nsec = 10 * 1000 * 1000;

    tmfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (tmfd < 0)
    {
        return -1;
    }

    ret = timerfd_settime(tmfd, 0, &new_value, NULL);
    if (ret < 0)
    {
        close(tmfd);
        return -1;
    }

    if (epoll_add_fd(tmfd))
    {
        close(tmfd);
        return -1;
    }
    g_timerfd = tmfd;

    return 0;
}

int main(int argc, char *argv[])
{
    int mode = 4; //默认双buffer
    if (argc >= 2)
    {
        mode = atoi(argv[1]);
    }
    lv_init();

    epollfd_init();
    timerfd_init();

    /*初始化fb后，会动态设置分辨率*/
    fbdev_init();

    my_app_init(argc, argv);

    /*A small buffer for LittlevGL to draw the screen's content*/
    lv_color_t *buf_1 = (lv_color_t *)alloca(sizeof(lv_color_t) * DISP_BUF_SIZE);
    lv_color_t *buf_2 = (lv_color_t *)alloca(sizeof(lv_color_t) * DISP_BUF_SIZE);

    /*Initialize a descriptor for the buffer*/
    static lv_disp_draw_buf_t disp_buf;
    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);

    /*Initialize and register a display driver*/
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = MY_UI_W_MAX;
    disp_drv.ver_res = MY_UI_H_MAX;

    switch (mode)
    {
    case 0: // 0度
    case 2: // 180度
        disp_drv.sw_rotate = 1;
        disp_drv.rotated = mode;
        break;
    case 1: // 90度
    case 3: // 270度
    {
        //宽高对调
        int tmp = MY_UI_W_MAX;
        MY_UI_W_MAX = MY_UI_H_MAX;
        MY_UI_H_MAX = tmp;
        MY_UI_W_ZOOM = MY_UI_W_MAX * 1.0 / MY_BASE_W_MAX;
        MY_UI_H_ZOOM = MY_UI_H_MAX * 1.0 / MY_BASE_H_MAX;
        
        disp_drv.sw_rotate = 1;
        disp_drv.rotated = mode;
    }

    break;
    case 4: //双bufferfb
        disp_drv.full_refresh = 1;
        break;
    default:
        printf("error! none cmd! see README.md\r\n");
        exit(1);
        break;
    }

    lv_disp_drv_register(&disp_drv);

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);

    evdev_init();
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = (void (*)(struct _lv_indev_drv_t *, lv_indev_data_t *))evdev_read; // defined in lv_drivers/indev/evdev.h
    indev_drv.feedback_cb = my_touch_feedback;
    lv_indev_t *lv_indev = lv_indev_drv_register(&indev_drv);
    if (!lv_indev)
    {
        printf("lv_indev rregister error %d \r\n", __LINE__);
        return 0;
    }

    // app
    my_app_main(argc, argv);

    return 0;
}

/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if (start_ms == 0)
    {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
