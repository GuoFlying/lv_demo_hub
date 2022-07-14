/*
 * @Author: Flying
 * @Date: 2022-05-02 17:15:11
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 17:15:36
 * @Description: 新建文件
 */
#include "../app.h"

/**
 * Reverse the order of flex items
 */
int app_flex_4(lv_obj_t *parent)
{

    lv_obj_t * cont = lv_obj_create(parent);
    lv_obj_set_size(cont, 300, 220);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN_REVERSE);

    uint32_t i;
    for(i = 0; i < 6; i++) {
        lv_obj_t * obj = lv_obj_create(cont);
        lv_obj_set_size(obj, 100, 50);

        lv_obj_t * label = lv_label_create(obj);
        lv_label_set_text_fmt(label, "Item: %"LV_PRIu32, i);
        lv_obj_center(label);
    }
    return 0;
}

