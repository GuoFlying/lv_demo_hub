/*
 * @Author: Flying
 * @Date: 2022-04-05 14:18:28
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-14 12:54:50
 * @Description: 新建文件
 */
#include "app_common.h"
#include "v_font.h"

/**
 * @description:
 * @param {lv_obj_t} *parent
 * @return {*}
 */
static lv_obj_t *app_common_item_parent_create(lv_obj_t *parent)
{
    lv_obj_t *cont = lv_obj_create(parent);
    lv_obj_set_size(cont, APP_UI_W_MAX, APP_UI_H_MAX);
    lv_obj_set_style_border_width(cont, 0, 0);
    lv_obj_set_style_pad_all(cont, 0, 0);
    lv_obj_set_style_radius(cont, 0, 0);
    return cont;
}

/**
 * @description:
 * @param {lv_event_t} *e
 * @return {*}
 */
static void event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code != LV_EVENT_CLICKED)
    {
        return;
    }

    lv_obj_t *common_obj = lv_obj_get_parent(obj);
    lv_obj_t *parent = lv_obj_get_parent(common_obj);

    lv_obj_t *app_cont = app_common_item_parent_create(parent);
    app_item_fun_t func = (app_item_fun_t)obj->user_data;
    int ret = 0;
    if (func)
    {
        ret = func(app_cont);
    }
    lv_obj_t *exit_obj = (lv_obj_t *)common_obj->user_data;
    if (ret == 0)
    { //需要创建返回按键
        exit_obj->user_data = app_cont;
        lv_obj_clear_flag(exit_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(common_obj, LV_OBJ_FLAG_HIDDEN);
        lv_obj_move_foreground(exit_obj);
    }
    else
    {
        lv_obj_del(exit_obj);
        lv_obj_del(common_obj);
    }
}

/**
 * @description: 通用退出按键
 * @param {lv_event_t} *e
 * @return {*}
 */
static void app_common_obj_del_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_t *common_obj = lv_event_get_user_data(e);

    if (code != LV_EVENT_CLICKED)
    {
        return;
    }

    if (obj->user_data)
    {
        lv_obj_del((lv_obj_t *)obj->user_data); //删除app item
        obj->user_data = NULL;
    }
    lv_obj_clear_flag(common_obj, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

/**
 * @description:
 * @param {lv_obj_t} *parent
 * @return {*}
 */
lv_obj_t *app_common_obj_create(const char *title, lv_obj_t *parent)
{
    lv_obj_t *lab = lv_label_create(parent);
    lv_label_set_text(lab, title);
    lv_obj_center(lab);
    lv_obj_set_style_text_color(lab, lv_color_black(), 0);
    lv_obj_align(lab, LV_ALIGN_TOP_MID, 0, 10);

    lv_obj_t *list1 = lv_list_create(parent);
    lv_obj_set_size(list1, APP_UI_W_MAX * 0.7, APP_UI_H_MAX * 0.9);
    lv_obj_set_style_pad_row(list1, 10 * APP_UI_H_ZOOM, LV_PART_MAIN);
    lv_obj_set_style_bg_opa(list1, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(list1, 0, 0);
    lv_obj_set_flex_align(list1, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    lv_obj_align_to(list1, lab, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

    lv_obj_t *exit_obj = lv_label_create(parent); //通用按键创建
    lv_label_set_text(exit_obj, LV_SYMBOL_CLOSE);
    lv_obj_set_style_text_font(exit_obj, &lv_font_montserrat_32, 0);
    lv_obj_set_style_pad_top(exit_obj, 5, LV_STATE_PRESSED);
    lv_obj_set_style_pad_left(exit_obj, 5, LV_STATE_PRESSED);
    lv_obj_set_style_text_font(exit_obj, &lv_font_montserrat_22, LV_STATE_PRESSED);
    lv_obj_set_style_text_color(exit_obj, lv_color_hex3(0xf00), 0);
    lv_obj_align(exit_obj, LV_ALIGN_TOP_RIGHT, -10, 10);
    lv_obj_add_event_cb(exit_obj, app_common_obj_del_cb, LV_EVENT_CLICKED, list1);
    lv_obj_add_flag(exit_obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_flag(exit_obj, LV_OBJ_FLAG_HIDDEN); //默认隐藏
    exit_obj->user_data = NULL;
    list1->user_data = exit_obj; //暂存

    return list1;
}

/**
 * @description:
 * @param {lv_obj_t} *common_obj
 * @param {char} *text
 * @param {app_fun_t} func
 * @return {*}
 */
void *app_common_obj_add_item(lv_obj_t *common_obj, const char *text, app_item_fun_t func)
{
    static int tmp_color = LV_PALETTE_RED;

    lv_obj_t *btn;
    btn = lv_btn_create(common_obj);
    lv_obj_set_style_bg_color(btn, lv_color_white(), 0);
    lv_obj_set_size(btn, APP_UI_W_MAX * 0.6, APP_UI_H_MAX * 0.1);
    // lv_obj_set_x(btn, lv_pct(10));
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_set_style_border_color(btn, lv_palette_main(tmp_color), 0);
    lv_obj_set_style_pad_all(btn, 0, 0);
    lv_obj_set_style_border_side(btn, LV_BORDER_SIDE_LEFT, 0);
    lv_obj_set_style_border_width(btn, 5 * APP_UI_H_ZOOM, 0);

    btn->user_data = func;

    lv_obj_t *lab = lv_label_create(btn);
    lv_label_set_text(lab, text);
    lv_obj_center(lab);
    lv_obj_set_style_text_color(lab, lv_color_black(), 0);
    lv_obj_set_style_text_font(lab, get_lv_font_by_size(14 * APP_UI_H_ZOOM), 0);

    if (++tmp_color > LV_PALETTE_GREY)
    {
        tmp_color = LV_PALETTE_RED;
    }
}