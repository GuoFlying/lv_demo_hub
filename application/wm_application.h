/*
 * @Author: Flying
 * @Date: 2022-03-23 21:12:14
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 20:50:23
 * @Description: 新建文件
 */
#pragma once
#include "../my_conf.h"
#include "../lvgl/lvgl.h"
#include "sys/wm_head.h"
#include "sys/wm_home_btn.h"
#include "sys/wm_body.h"
#include "sys/wm_footer.h"
#include "app/app.h"
#include "sys/wm_monitor.h"
#include "sys/wm_explain.h"
#include "hw_app/hw_app.h"

class wm_application
{
private:
    bool is_theme_dark;
    lv_obj_t *app_home;
    bool is_app;

    wm_head *head;
    wm_home_btn *home_btn;
    wm_body *body;
    wm_footer *footer;
    wm_monitor *about;
    wm_explain *explain;

    static void page_scroll_event_cb(int index, void *cb_arg);
    static void app_clicked_event_cb(int index, void *cb_arg);
    static void footer_event_cb(int index, void *cb_arg);
    static void home_btn_event_cb(int code, void *cb_arg);

    void show_app(lv_obj_t *cont);
    bool del_app();
    void change_theme();

public:
    wm_application();
    ~wm_application();
    void run();
};
