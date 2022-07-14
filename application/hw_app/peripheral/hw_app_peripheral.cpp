/*
 * @Author: Flying
 * @Date: 2022-05-15 20:44:27
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 21:06:34
 * @Description: 新建文件
 */

#include "../hw_app.h"
#include "../../../common/c_common.h"
#include <iostream>
using namespace std;
#include <string>

lv_obj_t *hw_app_peripheral()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "待办事项(TODO)");
    lv_obj_set_style_text_font(label, c_font::get_font(48 * MY_UI_W_ZOOM), 0);
    lv_obj_set_align(label, LV_ALIGN_TOP_MID);

    lv_obj_t *obj = lv_rlottie_create_from_file(parent, 200 * MY_UI_W_ZOOM, 200 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "peripheral.json");
    lv_obj_center(obj);

    return parent;
}
