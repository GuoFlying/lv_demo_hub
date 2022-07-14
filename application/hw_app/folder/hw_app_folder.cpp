/*
 * @Author: Flying
 * @Date: 2022-05-15 20:44:27
 * @LastEditors: Flying
 * @LastEditTime: 2022-06-22 22:40:30
 * @Description: 新建文件
 */

#include "../hw_app.h"
#include "../../../common/c_common.h"
#ifdef F_WINDOWS
lv_obj_t *hw_app_folder()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *label = lv_label_create(parent);
    lv_label_set_text(label, "详见ubuntu、linuxarm (windows TODO)");
    lv_obj_set_style_text_font(label, c_font::get_font(48 * MY_UI_W_ZOOM), 0);
    lv_obj_set_align(label, LV_ALIGN_TOP_MID);

    lv_obj_t *obj = lv_rlottie_create_from_file(parent, 200 * MY_UI_W_ZOOM, 200 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "folder.json");
    lv_obj_center(obj);

    return parent;
}

#else

#include "folder_browser.h"
#include <iostream>
using namespace std;
#include <string>

static void show_img(string tail_name, string file_name)
{
    lv_obj_t *mbox1 = lv_msgbox_create(NULL, file_name.data(), tail_name.data(), NULL, true);
    lv_obj_set_size(mbox1, LV_HOR_RES - 20, LV_VER_RES - 20);
    lv_obj_center(mbox1);

    string name = "S:" + tail_name + file_name;
    lv_obj_t *img = lv_img_create(mbox1);
    lv_img_set_src(img, name.data());
}

static void show_lottie(string tail_name, string file_name)
{
    lv_obj_t *mbox1 = lv_msgbox_create(NULL, file_name.data(), tail_name.data(), NULL, true);
    lv_obj_set_size(mbox1, LV_HOR_RES - 20, LV_VER_RES - 20);
    lv_obj_center(mbox1);

    string name = tail_name + file_name;
    lv_obj_t *obj = lv_rlottie_create_from_file(mbox1, 200 * MY_UI_W_ZOOM, 200 * MY_UI_H_ZOOM, name.data());
}

lv_obj_t *hw_app_folder()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    folder_browser *p_br = NULL;

    p_br = new folder_browser(parent);
    p_br->add_exec("png", show_img);
    p_br->add_exec("json", show_lottie);
    p_br->add_exec("bmp", show_img);

    return parent;
}

#endif