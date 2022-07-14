/*
 * @Author: Flying
 * @Date: 2022-04-05 14:24:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-26 21:18:54
 * @Description: 新建文件
 */
#include "../app.h"
int app_label_2(lv_obj_t *parent)
{
    /*Create a style for the shadow*/
    static lv_style_t style_shadow;
    lv_style_init(&style_shadow);
    lv_style_set_text_opa(&style_shadow, LV_OPA_30);
    lv_style_set_text_color(&style_shadow, lv_color_black());

    /*Create a label for the shadow first (it's in the background)*/
    lv_obj_t *shadow_label = lv_label_create(parent);
    lv_obj_add_style(shadow_label, &style_shadow, 0);

    /*Create the main label*/
    lv_obj_t *main_label = lv_label_create(parent);
    lv_label_set_text(main_label, "A simple method to create\n"
                                  "shadows on a text.\n"
                                  "It even works with\n\n"
                                  "newlines     and spaces.");

    /*Set the same text for the shadow label*/
    lv_label_set_text(shadow_label, lv_label_get_text(main_label));

    /*Position the main label*/
    lv_obj_align(main_label, LV_ALIGN_CENTER, 0, 0);

    /*Shift the second label down and to the right by 2 pixel*/
    lv_obj_align_to(shadow_label, main_label, LV_ALIGN_TOP_LEFT, 2, 2);
    return 0;
}
