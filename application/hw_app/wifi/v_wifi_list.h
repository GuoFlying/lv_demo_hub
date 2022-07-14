/*
 * @Author: Flying
 * @Date: 2022-07-06 22:37:49
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 21:27:56
 * @Description: 修改文件
 */
#pragma once
#include "../common/hw_app_base.h"
#include "../../../common/c_common.h"
#include <string>
#include <vector>
#include <list>

using v_wifi_connect_cb_t = void (*)(void *arg, const char *ssid, const char *pwd);
using v_wifi_disconnect_cb_t = void (*)(void *arg);

struct v_wifi_list_item
{
    uint16_t id;
    bool is_encrypt_key;
    std::string ssid;
    uint8_t channel;
    std::vector<uint8_t> mac;
    int8_t singnal;
    void *arg;
    v_wifi_list_item()
    {
        this->clear();
    }
    void clear()
    {
        id = 0;
        is_encrypt_key = false;
        ssid.clear();
        channel = 0;
        mac.clear();
        singnal = 0;
        arg = NULL;
    }
    v_wifi_list_item &operator=(v_wifi_list_item &p)
    {
        this->id = p.id;
        this->is_encrypt_key = p.is_encrypt_key;
        this->ssid = p.ssid;
        this->channel = p.channel;
        this->mac = p.mac;
        this->singnal = p.singnal;
        this->arg = p.arg;
        return *this;
    }
};

class v_wifi_list : public hw_app_base
{
private:
    lv_obj_t *cont;
    lv_obj_t *connect_cont;
    lv_obj_t *connect_btn;
    lv_obj_t *disconnect_cont;

    static void list_event_cb(lv_event_t *e);
    static void disconnect_event_cb(lv_event_t *e);
    static void passwd_ta_event_cb(lv_event_t *e);
    static void connect_wifi_event_cb(lv_event_t *e);
    static void exit_connect_widget_event_cb(lv_event_t *e);
    static void disconnect_wifi_event_cb(lv_event_t *e);
    static void exit_disconnect_widget_event_cb(lv_event_t *e);

    v_wifi_list_item connect_item;
    std::list<v_wifi_list_item> list_bk;
    std::string passwd_str;
    std::string ssid_str;
    v_wifi_connect_cb_t connect_cb;
    v_wifi_disconnect_cb_t disconnect_cb;
    void *arg;

    void add_list_item(v_wifi_list_item &item, bool highlight = false);
    void show_connect_widget(v_wifi_list_item &item);
    void show_disconnect_widget(v_wifi_list_item &item);

public:
    v_wifi_list(lv_obj_t *parent, v_wifi_connect_cb_t connect_cb = NULL, v_wifi_disconnect_cb_t disconnect_cb = NULL, void *arg = NULL);
    ~v_wifi_list();
    void clear();
    void show();
    void set_connect_item(v_wifi_list_item &item);
    void push_back_list(v_wifi_list_item &item);
};
