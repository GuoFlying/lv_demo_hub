/*
 * @Author: Flying
 * @Date: 2022-05-01 18:19:50
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 13:15:36
 * @Description: 新建文件
 */

#include "../app.h"

int app_img_6(lv_obj_t *parent)
{
    lv_obj_t *label;
    lv_obj_t *img;
    lv_obj_t *tab;

    lv_obj_t *tabview;
    tabview = lv_tabview_create(parent, LV_DIR_BOTTOM, 50);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    {
        tab = lv_tabview_add_tab(tabview, "bmp8");

        label = lv_label_create(tab);
        lv_obj_set_style_text_font(label, get_lv_font_by_size(20 * APP_UI_H_ZOOM), 0);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
        lv_label_set_text(label, MY_PNG_PATH "bmp/bmp8.bmp");

        img = lv_img_create(tab);
        lv_img_set_src(img, MY_PNG_PATH "bmp/bmp8.bmp");
        // lv_img_set_src(img, "S:lvgl/examples/libs/bmp/example_16bit.bmp");
        lv_obj_align_to(img, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10 * APP_UI_H_ZOOM);

        lv_img_set_zoom(img, 128);
    }

    {
        tab = lv_tabview_add_tab(tabview, "bmp16");

        label = lv_label_create(tab);
        lv_obj_set_style_text_font(label, get_lv_font_by_size(20 * APP_UI_H_ZOOM), 0);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
        lv_label_set_text(label, MY_PNG_PATH "bmp/bmp16.bmp");

        img = lv_img_create(tab);
        lv_img_set_src(img, MY_PNG_PATH "bmp/bmp16.bmp");
        // lv_img_set_src(img, "S:lvgl/examples/libs/bmp/example_16bit.bmp");
        lv_obj_align_to(img, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 110 * APP_UI_H_ZOOM);
        lv_img_set_zoom(img, 512);
    }

    {
        tab = lv_tabview_add_tab(tabview, "bmp24");

        label = lv_label_create(tab);
        lv_obj_set_style_text_font(label, get_lv_font_by_size(20 * APP_UI_H_ZOOM), 0);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
        lv_label_set_text(label, MY_PNG_PATH "bmp/bmp24.bmp");

        img = lv_img_create(tab);
        lv_img_set_src(img, MY_PNG_PATH "bmp/bmp24.bmp");
        // lv_img_set_src(img, "S:lvgl/examples/libs/bmp/example_16bit.bmp");
        lv_obj_align_to(img, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10 * APP_UI_H_ZOOM);
        lv_img_set_zoom(img, 200);
    }

    {
        tab = lv_tabview_add_tab(tabview, "bmp32");

        label = lv_label_create(tab);
        lv_obj_set_style_text_font(label, get_lv_font_by_size(20 * APP_UI_H_ZOOM), 0);
        lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 0);
        lv_label_set_text(label, MY_PNG_PATH "bmp/bmp32.bmp");

        img = lv_img_create(tab);
        lv_img_set_src(img, MY_PNG_PATH "bmp/bmp32.bmp");
        // lv_img_set_src(img, "S:lvgl/examples/libs/bmp/example_16bit.bmp");
        lv_obj_align_to(img, label, LV_ALIGN_OUT_BOTTOM_MID, 0, 10 * APP_UI_H_ZOOM);
    }

    lv_obj_scroll_to_view_recursive(label, LV_ANIM_ON);

    return 0;
}
