/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:26:57
 * @Description: 新建文件
 */

#include "../app.h"
static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);
    if (code == LV_EVENT_FOCUSED)
    {
        lv_keyboard_set_textarea(kb, ta);
        lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }

    if (code == LV_EVENT_DEFOCUSED)
    {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
    }
}

int app_keyboard_1(lv_obj_t *parent)
{
    /*Create a keyboard to use it with an of the text areas*/
    lv_obj_t *kb = lv_keyboard_create(parent);

    /*Create a text area. The keyboard will write here*/
    lv_obj_t *ta;
    ta = lv_textarea_create(parent);
    lv_obj_align(ta, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_textarea_set_placeholder_text(ta, "Hello");
    lv_obj_set_size(ta, 140, 80);

    ta = lv_textarea_create(parent);
    lv_obj_align(ta, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(ta, ta_event_cb, LV_EVENT_ALL, kb);
    lv_obj_set_size(ta, 140, 80);

    lv_keyboard_set_textarea(kb, ta);
    return 0;
}
