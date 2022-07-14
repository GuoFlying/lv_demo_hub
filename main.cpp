/*
 * @Author: Flying
 * @Date: 2021-10-28 08:12:53
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 15:13:01
 * @Description: file content
 */

#ifdef F_WINDOWS
#include "base_main_windows.h"
#endif

#ifdef F_UBUNTU
#include "base_main_ubuntu.h"
#endif

#ifdef F_LINUXARM
#include "base_main_linuxarm.h"
#endif

#if !LV_USE_BMP
#include "my_lib/my_bmp.h"
#endif

#include "lvgl/demos/lv_demos.h"
#include "lvgl/examples/lv_examples.h"
#include "application/wm_application.h"
static void my_touch_feedback(struct _lv_indev_drv_t *drv, unsigned char ev)
{
}

static void my_app_init(int argc, char *argv[])
{
#if !LV_USE_BMP
    my_bmp_init();
#endif
}

void my_app_main(int argc, char *argv[])
{

#define EXAMPLE_DEBUG 0

#if !EXAMPLE_DEBUG
    wm_application app;
#else
    lv_example_list_2();
#endif

#ifdef F_LINUXARM
    int i = 0;
    int fd_cnt = 0;
    int sfd;
    struct epoll_event events[EPOLL_LISTEN_CNT];
    int count = 0;
    memset(events, 0, sizeof(events));
    while (1)
    {
        /* wait epoll event */
        fd_cnt = epoll_wait(g_epollfd, events, EPOLL_LISTEN_CNT, EPOLL_LISTEN_TIMEOUT);
        for (i = 0; i < fd_cnt; i++)
        {
            sfd = events[i].data.fd;
            if (!(events[i].events & EPOLLIN))
            {
                continue;
            }
            if (sfd != g_timerfd)
            {
                continue;
            }
            uint64_t exp;
            read(sfd, &exp, sizeof(uint64_t));
            //每次进来10ms，限制20ms一次
            if ((count++) % 2 != 0)
            {
                continue;
            }
            // LV_LOG_USER("");
            // usleep(30*1000);
            lv_task_handler();
            app.run();
        }
    }
#endif

#ifdef F_UBUNTU
    while (1)
    {
        /* Periodically call the lv_task handler.
         * It could be done in a timer interrupt or an OS task too.*/
        lv_timer_handler();
#if !EXAMPLE_DEBUG
        app.run();
#endif
        usleep(20 * 1000);
    }
#endif

#ifdef F_WINDOWS
    while (!lv_win32_quit_signal)
    {
        // static DWORD old_t = 0, t;
        // old_t = t;
        if (run_time_flag >= 20)
        {
            // t = GetTickCount();
            // printf("%d\r\n", t-old_t);
            run_time_flag = 0;
#if !EXAMPLE_DEBUG
            app.run();
#endif
            lv_task_handler();
        }
        Sleep(1);
    }
#endif
}
