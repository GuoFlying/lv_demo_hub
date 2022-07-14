/*
 * @Author: Flying
 * @Date: 2022-03-25 22:16:25
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-10 23:40:41
 * @Description: 新建文件
 */
#pragma once

#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
typedef enum HOME_BTN_CODE_E_
{
    HOME_BTN_CODE_HOME,
    HOME_BTN_CODE_ABOUT,
    HOME_BTN_CODE_THEME,
    HOME_BTN_CODE_EXPLAIN,
} HOME_BTN_CODE_E;

typedef void (*home_btn_event_cb_t)(int code, void *cb_arg);
class wm_home_btn
{
private:
    lv_obj_t *cont;
    lv_obj_t *btn;
    lv_obj_t *btn_items[4];
    home_btn_event_cb_t cb;
    void *cb_arg;
    static void move_event_cb(lv_event_t *e);
    static void checkout_move_event_cb(lv_event_t *e);
    static void clicket_event_cb(lv_event_t *e);
    static void open_changer_anim_cb(void *var, int32_t v);
    static void items_clicket_event_cb(lv_event_t *e);

public:
    wm_home_btn(home_btn_event_cb_t cb = NULL, void *cb_arg = NULL);
    ~wm_home_btn();
};
