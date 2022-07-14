/*
 * @Author: Flying
 * @Date: 2022-05-01 22:18:19
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:19:43
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Create a pie chart
 */
int app_meter_4(lv_obj_t *parent)
{
    lv_obj_t *meter = lv_meter_create(parent);

    /*Remove the background and the circle from the middle*/
    lv_obj_remove_style(meter, NULL, LV_PART_MAIN);
    lv_obj_remove_style(meter, NULL, LV_PART_INDICATOR);

    lv_obj_set_size(meter, 200, 200);
    lv_obj_center(meter);

    /*Add a scale first with no ticks.*/
    lv_meter_scale_t *scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 0, 0, 0, lv_color_black());
    lv_meter_set_scale_range(meter, scale, 0, 100, 360, 0);

    /*Add a three arc indicator*/
    lv_coord_t indic_w = 100;
    lv_meter_indicator_t *indic1 = lv_meter_add_arc(meter, scale, indic_w, lv_palette_main(LV_PALETTE_ORANGE), 0);
    lv_meter_set_indicator_start_value(meter, indic1, 0);
    lv_meter_set_indicator_end_value(meter, indic1, 40);

    lv_meter_indicator_t *indic2 = lv_meter_add_arc(meter, scale, indic_w, lv_palette_main(LV_PALETTE_YELLOW), 0);
    lv_meter_set_indicator_start_value(meter, indic2, 40); /*Start from the previous*/
    lv_meter_set_indicator_end_value(meter, indic2, 80);

    lv_meter_indicator_t *indic3 = lv_meter_add_arc(meter, scale, indic_w, lv_palette_main(LV_PALETTE_DEEP_ORANGE), 0);
    lv_meter_set_indicator_start_value(meter, indic3, 80); /*Start from the previous*/
    lv_meter_set_indicator_end_value(meter, indic3, 100);
    return 0;
}
