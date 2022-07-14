/*
 * @Author: Flying
 * @Date: 2022-03-25 22:10:18
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-13 22:11:20
 * @Description: 新建文件
 */
#include "wm_head.h"
#include "stdio.h"
#include "string.h"

#ifdef F_WINDOWS
#include <windows.h>
#else
#include <time.h>
#endif
#include "../../common/c_common.h"

#define HEAD_HANDLE_SIZE (30 * MY_UI_H_ZOOM)
/**
 * @description:
 * @param {lv_obj_t} *parent
 * @return {*}
 */
wm_head::wm_head(lv_obj_t *parent)
{
    this->label_date = NULL;
    this->cont = lv_obj_create(parent);
    lv_obj_clear_flag(this->cont, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(this->cont, LV_OBJ_FLAG_SCROLL_ELASTIC);
    lv_obj_remove_style_all(this->cont);
    lv_obj_set_size(this->cont, MY_UI_W_MAX, MY_UI_H_MAX);
    /*设置滑动后的居中方式*/
    lv_obj_set_scroll_snap_y(this->cont, LV_SCROLL_SNAP_CENTER);

    this->vis_handle = lv_obj_create(this->cont);
    lv_obj_set_y(this->vis_handle, -HEAD_HANDLE_SIZE);
    lv_obj_set_size(this->vis_handle, MY_UI_W_MAX, MY_UI_H_MAX + HEAD_HANDLE_SIZE * 2);
    lv_obj_clear_flag(this->vis_handle, LV_OBJ_FLAG_SNAPABLE);

    // lv_obj_set_style_bg_color(player, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_pad_all(this->vis_handle, 0, 0);
    lv_obj_set_style_radius(this->vis_handle, 15 * MY_UI_H_ZOOM, 0);
    lv_obj_set_scroll_dir(this->vis_handle, LV_DIR_VER);
    lv_obj_set_style_border_width(this->vis_handle, 4 * MY_UI_H_ZOOM, 0);
    lv_obj_set_style_border_side(this->vis_handle, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_bg_opa(this->vis_handle, LV_OPA_90, 0);

    /* 透明obj,占位用*/
    this->placeholder1 = lv_obj_create(this->cont);
    lv_obj_remove_style_all(this->placeholder1);
    lv_obj_clear_flag(this->placeholder1, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_set_style_bg_color(this->placeholder1, lv_color_hex(0xff0000), 0);
    // lv_obj_set_style_bg_opa(this->placeholder1, LV_OPA_90, 0);

    this->placeholder2 = lv_obj_create(this->cont);
    lv_obj_remove_style_all(this->placeholder2);
    lv_obj_clear_flag(this->placeholder2, LV_OBJ_FLAG_CLICKABLE);
    // lv_obj_set_style_bg_color(this->placeholder2, lv_color_hex(0x00ff00), 0);
    // lv_obj_set_style_bg_opa(this->placeholder2, LV_OPA_90, 0);

    lv_obj_set_size(this->placeholder1, MY_UI_W_MAX, MY_UI_H_MAX);
    lv_obj_set_y(this->placeholder1, 0);

    lv_obj_set_size(this->placeholder2, MY_UI_W_MAX, MY_UI_H_MAX - HEAD_HANDLE_SIZE * 2);
    lv_obj_set_y(this->placeholder2, MY_UI_H_MAX + HEAD_HANDLE_SIZE);

    reset(LV_ANIM_OFF);

    create_about();

    this->date_timer = lv_timer_create(show_date, 1000, this);
    lv_timer_ready(this->date_timer);
}
/**
 * @description:
 * @param {*}
 * @return {*}
 */
wm_head::~wm_head()
{
    if (this->date_timer)
    {
        lv_timer_del(this->date_timer);
    }
}

lv_obj_t *wm_head::create_about()
{
    lv_obj_t *item_cont = lv_obj_create(this->vis_handle);
    lv_obj_remove_style_all(item_cont);
    lv_obj_set_pos(item_cont, 0, HEAD_HANDLE_SIZE);
    lv_obj_set_size(item_cont, MY_UI_W_MAX, MY_UI_H_MAX);
    lv_obj_set_flex_flow(item_cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(item_cont, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    {
        lv_obj_t *label = lv_label_create(item_cont);
        lv_obj_set_style_text_font(label, c_font::get_font(40 * MY_UI_H_ZOOM), 0);
        lv_label_set_text(label, "关于");
    }

    {
        lv_obj_t *label = lv_label_create(item_cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text(label, "作者: Flying");
    }

    {
        lv_obj_t *label = lv_label_create(item_cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_fmt(label, "软件版本: V%s", MY_VERSION);
    }

    {
        lv_obj_t *label = lv_label_create(item_cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_fmt(label, "LVGL core: V%d.%d.%d", lv_version_major(), lv_version_minor(), lv_version_patch());
    }

    {
        lv_obj_t *label = lv_label_create(item_cont);
        lv_obj_set_style_text_font(label, c_font::get_font(28 * MY_UI_H_ZOOM), 0);
        lv_label_set_text_static(label, "源码：https://gitee.com/mFlying/lv_demo_hub");
    }

    {
        lv_obj_t *obj = lv_rlottie_create_from_file(item_cont, 180 * MY_UI_W_ZOOM, 180 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "about.json");
    }

    {
        lv_obj_t *obj = lv_rlottie_create_from_file(item_cont, 180 * MY_UI_W_ZOOM, 180 * MY_UI_H_ZOOM, MY_LOTTIE_PATH "scroll-top.json");
    }

    return item_cont;
}

void wm_head::reset(lv_anim_enable_t anim_en)
{
    lv_obj_scroll_to_view(this->placeholder2, anim_en);
}

/**
 * @description:
 * @param {lv_timer_t} *t
 * @return {*}
 */
void wm_head::show_date(lv_timer_t *t)
{
    wm_head *_this = (wm_head *)t->user_data;

#if F_WINDOWS
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    char buff[128];
    sprintf(buff, "%02d.%02d.%d %02d:%02d:%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);
    _this->set_date_str(buff);
#else
    time_t timep;
    struct tm *p;
    time(&timep);
    p = gmtime(&timep);
    char buff[128];
    sprintf(buff, "%02d.%02d.%d %02d:%02d:%02d", p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    _this->set_date_str(buff);

#endif
}

/**
 * @description:
 * @param {char} *buff
 * @return {*}
 */
void wm_head::set_date_str(char *buff)
{
    if (this->label_date)
    {
        lv_label_set_text(this->label_date, buff);
        return;
    }
    this->label_date = lv_label_create(this->vis_handle);
    lv_obj_set_style_text_font(this->label_date, c_font::get_font(14 * MY_UI_W_ZOOM), 0);
    lv_obj_align(this->label_date, LV_ALIGN_BOTTOM_LEFT, 10 * MY_UI_H_ZOOM, -5 * MY_UI_H_ZOOM);
    lv_label_set_text(this->label_date, buff);
}
