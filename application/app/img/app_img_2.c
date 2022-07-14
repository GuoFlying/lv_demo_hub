/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:34:35
 * @Description: 新建文件
 */

#include "../app.h"
static lv_obj_t *create_slider(lv_obj_t *parent, lv_color_t color);
static void slider_event_cb(lv_event_t *e);

static lv_obj_t *red_slider, *green_slider, *blue_slider, *intense_slider;
static lv_obj_t *img1;

/**
 * Demonstrate runtime image re-coloring
 */
int app_img_2(lv_obj_t *parent)
{
    /*Create 4 sliders to adjust RGB color and re-color intensity*/
    red_slider = create_slider(parent, lv_palette_main(LV_PALETTE_RED));
    green_slider = create_slider(parent, lv_palette_main(LV_PALETTE_GREEN));
    blue_slider = create_slider(parent, lv_palette_main(LV_PALETTE_BLUE));
    intense_slider = create_slider(parent, lv_palette_main(LV_PALETTE_GREY));

    lv_slider_set_value(red_slider, LV_OPA_20, LV_ANIM_OFF);
    lv_slider_set_value(green_slider, LV_OPA_90, LV_ANIM_OFF);
    lv_slider_set_value(blue_slider, LV_OPA_60, LV_ANIM_OFF);
    lv_slider_set_value(intense_slider, LV_OPA_50, LV_ANIM_OFF);

    lv_obj_align(red_slider, LV_ALIGN_LEFT_MID, 25, 0);
    lv_obj_align_to(green_slider, red_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);
    lv_obj_align_to(blue_slider, green_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);
    lv_obj_align_to(intense_slider, blue_slider, LV_ALIGN_OUT_RIGHT_MID, 25, 0);

    /*Now create the actual image*/
    LV_IMG_DECLARE(app_img_cogwheel_argb)
    img1 = lv_img_create(parent);
    lv_img_set_src(img1, &app_img_cogwheel_argb);
    lv_obj_align(img1, LV_ALIGN_RIGHT_MID, -20, 0);

    lv_event_send(intense_slider, LV_EVENT_VALUE_CHANGED, NULL);
    return 0;
}

static void slider_event_cb(lv_event_t *e)
{
    LV_UNUSED(e);

    /*Recolor the image based on the sliders' values*/
    lv_color_t color = lv_color_make(lv_slider_get_value(red_slider), lv_slider_get_value(green_slider),
                                     lv_slider_get_value(blue_slider));
    lv_opa_t intense = lv_slider_get_value(intense_slider);
    lv_obj_set_style_img_recolor_opa(img1, intense, 0);
    lv_obj_set_style_img_recolor(img1, color, 0);
}

static lv_obj_t *create_slider(lv_obj_t *parent, lv_color_t color)
{
    lv_obj_t *slider = lv_slider_create(parent);
    lv_slider_set_range(slider, 0, 255);
    lv_obj_set_size(slider, 10, 200);
    lv_obj_set_style_bg_color(slider, color, LV_PART_KNOB);
    lv_obj_set_style_bg_color(slider, lv_color_darken(color, LV_OPA_40), LV_PART_INDICATOR);
    lv_obj_add_event_cb(slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    return slider;
}
