/*
 * @Author: Flying
 * @Date: 2022-05-15 11:14:38
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 11:23:13
 * @Description: 新建文件
 */

#include "../app.h"
#include "../common/v_font.h"
static lv_obj_t *level_label;

static void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);
    lv_obj_t *memory_game = lv_event_get_user_data(e);

    lv_100ask_memory_game_set_map(memory_game, lv_slider_get_value(slider), lv_slider_get_value(slider));
    lv_label_set_text_fmt(level_label, "%d*%d", lv_100ask_memory_game_get_row(memory_game), lv_100ask_memory_game_get_row(memory_game));
}

int game_100ask(lv_obj_t *parent)
{
    lv_obj_t *memory_game = lv_100ask_memory_game_create(parent);
    lv_obj_set_size(memory_game, 300 * APP_UI_W_ZOOM, 300 * APP_UI_H_ZOOM);
    // lv_100ask_memory_set_map(memory_game, 2, 2);
    lv_obj_set_style_text_font(memory_game, get_lv_font_by_size(30 * APP_UI_H_ZOOM), 0);
    lv_obj_center(memory_game);

    lv_obj_t *slider = lv_slider_create(parent);
    lv_obj_align_to(slider, memory_game, LV_ALIGN_OUT_BOTTOM_MID, 0, 10 * APP_UI_H_ZOOM);
    lv_slider_set_range(slider, 2, 10);
    lv_slider_set_value(slider, lv_100ask_memory_game_get_row(memory_game), LV_ANIM_ON);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, memory_game);

    level_label = lv_label_create(parent);
    lv_obj_set_style_text_font(level_label, get_lv_font_by_size(14 * APP_UI_H_ZOOM), 0);
    lv_label_set_text_fmt(level_label, "%d*%d", lv_100ask_memory_game_get_row(memory_game), lv_100ask_memory_game_get_row(memory_game));

    lv_obj_align_to(level_label, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 5 * APP_UI_H_ZOOM);
    return 0;
}
