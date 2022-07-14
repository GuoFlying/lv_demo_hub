/*
 * @Author: Flying
 * @Date: 2022-04-05 14:25:47
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-26 21:18:30
 * @Description: 新建文件
 */
#include "../app.h"
int  app_label_5(lv_obj_t *parent)
{
    static lv_anim_t animation_template;
    static lv_style_t label_style;

    lv_anim_init(&animation_template);
    lv_anim_set_delay(&animation_template, 1000); /*Wait 1 second to start the first scroll*/
    lv_anim_set_repeat_delay(&animation_template,
                             3000); /*Repeat the scroll 3 seconds after the label scrolls back to the initial position*/

    /*Initialize the label style with the animation template*/
    lv_style_init(&label_style);
    lv_style_set_anim(&label_style, &animation_template);

    lv_obj_t *label1 = lv_label_create(parent);
    lv_label_set_long_mode(label1, LV_LABEL_LONG_SCROLL_CIRCULAR); /*Circular scroll*/
    lv_obj_set_width(label1, 150);
    lv_label_set_text(label1, "It is a circularly scrolling text. ");
    lv_obj_align(label1, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_style(label1, &label_style, LV_STATE_DEFAULT); /*Add the style to the label*/
    
    return 0;
}
