/*
 * @Author: Flying
 * @Date: 2022-04-05 14:25:32
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-26 21:18:43
 * @Description: 新建文件
 */
#include "../app.h"
int app_label_3(lv_obj_t *parent)
{
    lv_obj_t *ltr_label = lv_label_create(parent);
    lv_label_set_text(ltr_label, "In modern terminology, a microcontroller is similar to a system on a chip (SoC).");
    lv_obj_set_style_text_font(ltr_label, &lv_font_montserrat_16, 0);
    lv_obj_set_width(ltr_label, 310);
    lv_obj_align(ltr_label, LV_ALIGN_TOP_LEFT, 5, 5);

    lv_obj_t *rtl_label = lv_label_create(parent);
    lv_label_set_text(rtl_label,
                      "מעבד, או בשמו המלא יחידת עיבוד מרכזית (באנגלית: CPU - Central Processing Unit).");
    lv_obj_set_style_base_dir(rtl_label, LV_BASE_DIR_RTL, 0);
    lv_obj_set_style_text_font(rtl_label, &lv_font_dejavu_16_persian_hebrew, 0);
    lv_obj_set_width(rtl_label, 310);
    lv_obj_align(rtl_label, LV_ALIGN_LEFT_MID, 5, 0);

    lv_obj_t *cz_label = lv_label_create(parent);
    lv_label_set_text(cz_label,
                      "嵌入式系统（Embedded System），\n是一种嵌入机械或电气系统内部、具有专一功能和实时计算性能的计算机系统。");
    lv_obj_set_style_text_font(cz_label, &lv_font_simsun_16_cjk, 0);
    lv_obj_set_width(cz_label, 310);
    lv_obj_align(cz_label, LV_ALIGN_BOTTOM_LEFT, 5, -5);
    return 0;
}
