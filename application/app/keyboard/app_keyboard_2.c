/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 12:13:56
 * @Description: 新建文件
 */

#include "../app.h"
#include "../common/v_font.h"
static void ta_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *ta = lv_event_get_target(e);
    lv_obj_t *kb = lv_event_get_user_data(e);

    if (code == LV_EVENT_FOCUSED)
    {
        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD)
        {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
        }
    }
    else if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
    {
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta); /*To forget the last clicked object to make it focusable again*/
    }
}

int app_keyboard_2(lv_obj_t *parent)
{
    lv_obj_t *kb = lv_100ask_chinese_ime_create(parent);
    lv_100ask_chinese_ime_set_text_font(get_lv_font_by_size(14 * APP_UI_H_ZOOM), 0); // set font
    // lv_chinese_ime_set_dict(your_dict); // Use a custom thesaurus. If it is not set, the built-in thesaurus will be used

    /* ta1 */
    lv_obj_t *ta1 = lv_textarea_create(parent);
    lv_obj_set_style_text_font(ta1, get_lv_font_by_size(14 * APP_UI_H_ZOOM), 0); // set font
    lv_obj_align(ta1, LV_ALIGN_TOP_LEFT, 10, 10);

    lv_keyboard_set_textarea(kb, ta1);

    lv_obj_add_event_cb(ta1, ta_event_cb, LV_EVENT_ALL, kb);

    /* ta2 */
    lv_obj_t *ta2 = lv_textarea_create(parent);
    lv_obj_set_style_text_font(ta2, get_lv_font_by_size(14 * APP_UI_H_ZOOM), 0); // set font
    lv_obj_align_to(ta2, ta1, LV_ALIGN_OUT_RIGHT_MID, 10, 0);

    lv_obj_add_event_cb(ta2, ta_event_cb, LV_EVENT_ALL, kb);
    return 0;
}
