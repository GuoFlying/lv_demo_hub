/*
 * @Author: Flying
 * @Date: 2022-04-29 15:06:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-29 22:31:43
 * @Description: 新建文件
 */
#include "../app.h"
#include "lv_mini3d.h"
static void btn_render_event(lv_event_t *e)
{
    lv_obj_t *mini3d = (lv_obj_t *)lv_event_get_user_data(e);
    static int index = 1;
    int renders = LV_RENDER_STATE_WIREFRAME | LV_RENDER_STATE_TEXTURE | LV_RENDER_STATE_COLOR;

    lv_mini3d_set_render(mini3d, index);
    if (++index > renders)
    {
        index = 1;
    }
}

static void slider_x_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *mini3d = lv_event_get_user_data(e);

    int32_t v = lv_slider_get_value(obj);
    float tmp = 1 + (v - 3500) / 1000.0f;
    lv_mini3d_set_alpha(mini3d, tmp);
}

static void slider_y_event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *mini3d = lv_event_get_user_data(e);

    int32_t v = lv_slider_get_value(obj);
    float tmp = 3.5 + (v - 150) / 100.0f;
    lv_mini3d_set_pos(mini3d, tmp);
}

lv_obj_t *app_mini3d()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    // lv_obj_set_style_bg_color(parent, lv_color_hex(0x000000), 0);

    lv_obj_t *mini3d = lv_mini3d_create(parent, 300, 300);
    lv_obj_set_size(mini3d, 300, 300);
    lv_obj_center(mini3d);

    {
        lv_obj_t *btn = lv_btn_create(parent);
        lv_obj_set_size(btn, 240, 34);
        lv_obj_align_to(btn, mini3d, LV_ALIGN_OUT_TOP_MID, 0, -20);
        lv_obj_add_event_cb(btn, btn_render_event, LV_EVENT_CLICKED, mini3d);

        lv_obj_t *label = lv_label_create(btn);
        lv_label_set_text(label, "切换渲染方式");
        lv_obj_set_style_text_font(label, get_lv_font_by_size(12), 0);
        lv_obj_center(label);
    }

    lv_obj_t *slider;
    slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 0, 7000);
    lv_slider_set_value(slider, 3500, LV_ANIM_OFF);
    lv_obj_add_event_cb(slider, slider_x_event_cb, LV_EVENT_VALUE_CHANGED, mini3d);
    lv_obj_set_size(slider, 200, 10);
    lv_obj_align_to(slider, mini3d, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);

    slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 0, 1000);
    lv_slider_set_value(slider, 150, LV_ANIM_OFF);
    lv_obj_add_event_cb(slider, slider_y_event_cb, LV_EVENT_VALUE_CHANGED, mini3d);
    lv_obj_set_size(slider, 10, 200);
    lv_obj_align_to(slider, mini3d, LV_ALIGN_OUT_RIGHT_MID, 20, 0);
    return parent;
}
