/*
 * @Author: Flying
 * @Date: 2022-06-22 22:29:14
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 21:31:34
 * @Description: 修改文件
 */
#pragma once
#ifdef F_LINUXARM
#include "../common/hw_app_base.h"
#include <string>
#include <map>
#include "wifi_config.h"
#include "v_wifi_list.h"

class wifi_widget : public hw_app_base
{
private:
    lv_obj_t *loading;
    v_wifi_list *wifi_list;
    lv_timer_t *timer;
    wifi_config *config;

    static void run(lv_timer_t *t);
    static void open_cb(void *arg, void *req);
    static void state_cb(void *arg, void *req);
    static void wifi_scan_cb(void *arg, void *req);
    static void connect_ctr_cb(void *arg, const char *ssid, const char *pwd);
    static void disconnect_ctr_cb(void *arg);
    static void disconnect_cb(void *arg, void *req);

    void show_loading();
    void del_loading();

public:
    wifi_widget(lv_obj_t *parent);
    ~wifi_widget();
};
#endif