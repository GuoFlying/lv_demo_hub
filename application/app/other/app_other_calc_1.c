/*
 * @Author: Flying
 * @Date: 2022-05-01 22:51:10
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-14 23:51:51
 * @Description: 新建文件
 */
#include "../app.h"
#include "../common/v_font.h"
int app_other_calc_1(lv_obj_t *parent)
{
    lv_obj_t *calc = lv_100ask_calc_create(parent);
    lv_obj_set_size(calc, 480 * APP_UI_W_ZOOM, 600 * APP_UI_H_ZOOM);
    lv_obj_center(calc);

    lv_obj_t *calc_ta_hist = lv_100ask_calc_get_ta_hist(calc);
    lv_obj_set_style_text_font(calc_ta_hist, get_lv_font_by_size(14 * APP_UI_W_ZOOM), 0);

    lv_obj_t *calc_ta_input = lv_100ask_calc_get_ta_input(calc);
    lv_obj_set_style_text_font(calc_ta_input, get_lv_font_by_size(20 * APP_UI_W_ZOOM), 0);

    lv_obj_t *calc_ta_btnm = lv_100ask_calc_get_btnm(calc);
    lv_obj_set_style_text_font(calc_ta_btnm, get_lv_font_by_size(18 * APP_UI_W_ZOOM), 0);
    return 0;
}
