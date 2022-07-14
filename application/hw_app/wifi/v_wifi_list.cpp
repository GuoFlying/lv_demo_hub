/*
 * @Author: Flying
 * @Date: 2022-07-06 22:37:57
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 21:27:23
 * @Description: 修改文件
 */
#include "v_wifi_list.h"
#include <string>
using namespace std;

v_wifi_list::v_wifi_list(lv_obj_t *parent, v_wifi_connect_cb_t connect_cb, v_wifi_disconnect_cb_t disconnect_cb, void *arg)
    : hw_app_base(parent)
{
    /*Create a list*/
    this->connect_cont = NULL;
    this->disconnect_cont = NULL;
    this->connect_cb = connect_cb;
    this->disconnect_cb = disconnect_cb;
    this->arg = arg;

    cont = lv_list_create(parent);
    lv_obj_set_size(cont, 800 * MY_UI_W_ZOOM, 480 * MY_UI_H_ZOOM);
    lv_obj_center(cont);

    lv_obj_t *label = lv_label_create(parent);
    lv_obj_set_style_text_font(label, c_font::get_font(30 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
    lv_label_set_text_static(label, "WLAN");
}

v_wifi_list::~v_wifi_list()
{
}

void v_wifi_list::clear()
{
    list_bk.clear();
    connect_item.clear();
    this->show();
}

void v_wifi_list::show()
{
    for (int i = lv_obj_get_child_cnt(this->cont) - 1; i >= 0; i--)
    {
        lv_obj_t *obj = lv_obj_get_child(this->cont, i);
        if (obj)
        {
            lv_obj_del(obj);
        }
    }

    if (this->connect_item.ssid.length() > 0)
    {
        lv_obj_t *label = lv_list_add_text(cont, "已连接 WLAN");
        lv_obj_center(label);
        lv_obj_set_style_text_font(label, c_font::get_font(26 * MY_UI_H_ZOOM), 0);
        lv_obj_set_style_pad_bottom(label, 10 * MY_UI_H_ZOOM, 0);
        this->add_list_item(this->connect_item, true);
    }

    if (this->list_bk.size() <= 0)
    {
        return;
    }
    lv_obj_t *label = lv_list_add_text(cont, "可用 WLAN 列表");
    lv_obj_center(label);
    lv_obj_set_style_text_font(label, c_font::get_font(26 * MY_UI_H_ZOOM), 0);
    lv_obj_set_style_pad_bottom(label, 10 * MY_UI_H_ZOOM, 0);

    for (auto item : this->list_bk)
    {
        if (item.ssid == this->connect_item.ssid)
        {
            continue;
        }
        this->add_list_item(item);
    }
}

void v_wifi_list::add_list_item(v_wifi_list_item &item, bool highlight)
{
    lv_obj_t *btn;
    uint16_t icon = 0xe671;
    if (item.singnal > -50)
    { // 4
        icon += 0;
    }
    else if (item.singnal > -60)
    { // 3
        icon += 1;
    }
    else if (item.singnal > -70)
    { // 2
        icon += 2;
    }
    else
    { // 1
        icon += 3;
    }
    btn = lv_list_add_btn(cont, c_font::get_utf8(icon).data(), item.ssid.data());
    lv_obj_set_style_text_font(lv_obj_get_child(btn, 0), c_font::get_icon_font(26 * MY_UI_H_ZOOM), 0);
    lv_obj_set_style_text_font(lv_obj_get_child(btn, 1), c_font::get_font(26 * MY_UI_H_ZOOM), 0);
    lv_obj_set_style_pad_top(lv_obj_get_child(btn, 1), -10 * MY_UI_H_ZOOM, 0);
    if (highlight)
    {
        lv_obj_set_style_text_color(lv_obj_get_child(btn, 0), lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);
        lv_obj_set_style_text_color(lv_obj_get_child(btn, 1), lv_palette_main(LV_PALETTE_LIGHT_BLUE), 0);
    }

    lv_obj_add_event_cb(btn, v_wifi_list::list_event_cb, LV_EVENT_CLICKED, this);
}

void v_wifi_list::set_connect_item(v_wifi_list_item &item)
{
    this->connect_item = item;
}

void v_wifi_list::push_back_list(v_wifi_list_item &item)
{
    list_bk.push_back(item);
}

void v_wifi_list::list_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);

    if (code != LV_EVENT_CLICKED)
    {
        return;
    }
    uint32_t i;
    string ssid = "";
    for (i = 0; i < lv_obj_get_child_cnt(obj); i++)
    {
        lv_obj_t *child = lv_obj_get_child(obj, i);
        if (lv_obj_check_type(child, &lv_label_class))
        {
            ssid = lv_label_get_text(child);
            break;
        }
    }
    if (ssid.length() <= 0)
    {
        return;
    }
    if (_this->connect_item.ssid == ssid)
    {
        LV_LOG_USER("已连接： wifi %s", ssid.data());
        _this->show_disconnect_widget(_this->connect_item);
        return;
    }
    for (auto item : _this->list_bk)
    {
        if (item.ssid == ssid)
        {
            LV_LOG_USER("可用的wifi %s", ssid.data());
            _this->show_connect_widget(item);
            return;
        }
    }
}

void v_wifi_list::show_connect_widget(v_wifi_list_item &item)
{
    this->passwd_str.clear();
    this->ssid_str = item.ssid;

    this->connect_cont = lv_obj_create(this->parent);
    lv_obj_set_size(this->connect_cont, lv_pct(100), lv_pct(100));
    lv_obj_move_foreground(this->connect_cont);

    lv_obj_t *label = lv_label_create(this->connect_cont);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_label_set_text_static(label, "帐号： ");

    lv_obj_t *ssid = lv_label_create(this->connect_cont);
    lv_label_set_text(ssid, item.ssid.data());
    lv_obj_set_style_text_font(ssid, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align_to(ssid, label, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    label = lv_label_create(this->connect_cont);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 50 * MY_UI_H_ZOOM);
    lv_label_set_text_static(label, "密码:  ");

    lv_obj_t *ta = lv_textarea_create(this->connect_cont);
    lv_obj_align_to(ta, label, LV_ALIGN_OUT_RIGHT_TOP, 0, -5 * MY_UI_H_ZOOM);
    lv_textarea_set_placeholder_text(ta, "password");
    lv_obj_set_size(ta, 140, 40);
    // lv_textarea_set_password_mode(ta, true);
    lv_textarea_set_one_line(ta, true);
    lv_obj_add_event_cb(ta, passwd_ta_event_cb, LV_EVENT_ALL, this);

    lv_obj_t *kb = lv_keyboard_create(this->connect_cont);
    lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_keyboard_set_textarea(kb, ta);

    this->connect_btn = lv_btn_create(this->connect_cont);
    lv_obj_align(this->connect_btn, LV_ALIGN_TOP_LEFT, 0, 100 * MY_UI_H_ZOOM);
    lv_obj_set_size(this->connect_btn, 100 * MY_UI_H_ZOOM, 40 * MY_UI_H_ZOOM);
    label = lv_label_create(this->connect_btn);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
    lv_label_set_text_static(label, "连接");
    lv_obj_add_event_cb(this->connect_btn, connect_wifi_event_cb, LV_EVENT_CLICKED, this);
    lv_obj_add_state(this->connect_btn, LV_STATE_DISABLED);

    lv_obj_t *btn = lv_btn_create(this->connect_cont);
    lv_obj_align(btn, LV_ALIGN_TOP_LEFT, 150 * MY_UI_W_ZOOM, 100 * MY_UI_H_ZOOM);
    lv_obj_set_size(btn, 100 * MY_UI_H_ZOOM, 40 * MY_UI_H_ZOOM);
    label = lv_label_create(btn);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
    lv_label_set_text_static(label, "退出");
    lv_obj_add_event_cb(btn, exit_connect_widget_event_cb, LV_EVENT_CLICKED, this);
}

void v_wifi_list::show_disconnect_widget(v_wifi_list_item &item)
{
    this->disconnect_cont = lv_obj_create(this->parent);
    lv_obj_set_size(this->disconnect_cont, lv_pct(100), lv_pct(100));
    lv_obj_move_foreground(this->disconnect_cont);

    lv_obj_t *btn = lv_btn_create(this->disconnect_cont);
    lv_obj_align(btn, LV_ALIGN_CENTER, -100 * MY_UI_H_ZOOM, 0);
    lv_obj_set_size(btn, 100 * MY_UI_H_ZOOM, 40 * MY_UI_H_ZOOM);

    lv_obj_t *label = lv_label_create(btn);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
    lv_label_set_text_static(label, "断开");
    lv_obj_add_event_cb(btn, disconnect_wifi_event_cb, LV_EVENT_CLICKED, this);

    btn = lv_btn_create(this->disconnect_cont);
    lv_obj_align(btn, LV_ALIGN_CENTER, 100 * MY_UI_H_ZOOM, 0 * MY_UI_H_ZOOM);
    lv_obj_set_size(btn, 100 * MY_UI_H_ZOOM, 40 * MY_UI_H_ZOOM);

    label = lv_label_create(btn);
    lv_obj_set_style_text_font(label, c_font::get_font(14 * MY_UI_H_ZOOM), 0);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, -5 * MY_UI_H_ZOOM);
    lv_label_set_text_static(label, "退出");
    lv_obj_add_event_cb(btn, exit_disconnect_widget_event_cb, LV_EVENT_CLICKED, this);
}

void v_wifi_list::passwd_ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        _this->passwd_str = lv_textarea_get_text(ta);
        if (_this->passwd_str.length() >= 8)
        {
            lv_obj_clear_state(_this->connect_btn, LV_STATE_DISABLED);
        }
        else
        {
            lv_obj_add_state(_this->connect_btn, LV_STATE_DISABLED);
        }
    }
}

void v_wifi_list::connect_wifi_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);
    lv_obj_del(_this->connect_cont);
    _this->connect_cont = NULL;
    if (_this->connect_cb)
        _this->connect_cb(_this->arg, _this->ssid_str.data(), _this->passwd_str.data());
}

void v_wifi_list::exit_connect_widget_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);
    lv_obj_del(_this->connect_cont);
    _this->connect_cont = NULL;
}

void v_wifi_list::disconnect_wifi_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);
    lv_obj_del(_this->disconnect_cont);
    _this->disconnect_cont = NULL;
    if (_this->disconnect_cb)
        _this->disconnect_cb(_this->arg);
}

void v_wifi_list::exit_disconnect_widget_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    v_wifi_list *_this = (v_wifi_list *)lv_event_get_user_data(e);
    lv_obj_del(_this->disconnect_cont);
    _this->disconnect_cont = NULL;
}