/*
 * @Author: Flying
 * @Date: 2022-05-21 12:13:05
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-21 16:47:03
 * @Description: 修改文件
 */
#include "folder_browser.h"
#include <iostream>
using namespace std;
#include <string>
folder_browser::folder_browser(lv_obj_t *parent)
    : hw_app_base(parent)
{
    this->path = "";
    this->rows.nfiles = 0;
    this->rows.row = NULL;

    t_label = lv_label_create(parent);
    lv_label_set_text(t_label, "File Browser");
    lv_obj_set_style_text_font(t_label, c_font::get_font(32 * MY_UI_W_ZOOM), 0);
    lv_obj_set_width(t_label, MY_UI_W_MAX);
    lv_label_set_long_mode(t_label, LV_LABEL_LONG_SCROLL);
    lv_obj_set_style_text_align(t_label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_style_text_color(t_label, lv_color_hex(0x0000ff), 0);
    lv_obj_align(t_label, LV_ALIGN_TOP_MID, 0, 0);

    this->obj_list = lv_list_create(parent);
    lv_obj_set_size(this->obj_list, LV_HOR_RES - 50, LV_VER_RES - 100);
    lv_obj_align_to(this->obj_list, t_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_obj_set_style_text_font(this->obj_list, c_font::get_font(14 * MY_UI_W_ZOOM), 0);
    lv_obj_set_style_pad_row(this->obj_list, 5, 0);

    char new_path[FILE_PATH_MAX];
    memcpy(new_path, this->path.data(), FILE_PATH_MAX);

    //当前运行程序的目录
    int res = file_rover_get_row_cwd(new_path, &this->rows);
    if (res != 0)
    {
        return;
    }
    this->path = new_path;

    this->file_update_list();
}

folder_browser::~folder_browser()
{
}

void folder_browser::file_clear_list()
{
    uint32_t cnt = lv_obj_get_child_cnt(this->obj_list);
    for (int i = 0; i < cnt; i++)
    {
        lv_obj_t *obj = lv_obj_get_child(this->obj_list, 0);
        lv_obj_del(obj);
    }
}

/**
 * @description: 更新文件列表
 * @return {*}
 */
void folder_browser::file_update_list()
{
    f_row_list_t *p_rows = &this->rows;

    lv_obj_t *btn;
    lv_obj_t *label;
    char buf[100] = {0};

    file_clear_list();

    //添加标题
    lv_label_set_text(this->t_label, this->path.data());
    label = lv_list_add_text(this->obj_list, this->path.data());
    lv_obj_set_height(label, 30 * MY_UI_H_ZOOM);
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);

    LV_LOG_USER("%s", this->path.data());
    if (0 != strcmp(this->path.data(), "/"))
    {
        btn = lv_list_add_btn(this->obj_list, NULL, ". .");
        lv_obj_add_event_cb(btn, dir_event_handler, LV_EVENT_CLICKED, this);
    }

    for (int i = 0; i < p_rows->nfiles && i < FILE_LIST_SIZE_MAX; i++)
    {
        if (file_rover_is_dir(p_rows->row[i].mode))
        { //文件夹
            btn = lv_list_add_btn(this->obj_list, NULL, p_rows->row[i].name);
            lv_obj_add_event_cb(btn, dir_event_handler, LV_EVENT_CLICKED, this);
        }
        else
        { //文件
            btn = lv_list_add_btn(this->obj_list, NULL, p_rows->row[i].name);
            lv_obj_add_event_cb(btn, file_event_handler, LV_EVENT_CLICKED, this);
            label = lv_label_create(btn);
            lv_obj_align(label, LV_ALIGN_RIGHT_MID, -10, 0);
            file_rover_get_size_buf(buf, p_rows->row[i].size);
            lv_label_set_text(label, buf);
        }
    }
}

/**
 * @description: 点击文件夹回调
 * @param undefined
 * @return {*}
 */
void folder_browser::dir_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    folder_browser *_this = (folder_browser *)lv_event_get_user_data(e);
    if (code != LV_EVENT_CLICKED)
    {
        return;
    }
    char *text = (char *)lv_list_get_btn_text(_this->obj_list, obj);

    LV_LOG_USER("Clicked: %s", text);

    char new_path[FILE_PATH_MAX];
    memcpy(new_path, _this->path.data(), FILE_PATH_MAX);
    if (0 == strcmp(". .", text))
    {
        int res = file_rover_get_row_up(_this->path.data(), new_path, &_this->rows);
        if (res == 0)
        { //更新列表
            _this->path = new_path;
            _this->file_update_list();
        }
    }
    else
    {
        strncat(new_path, text, FILE_PATH_MAX);
        LV_LOG_USER("%s", new_path);
        int res = file_rover_get_row_down(new_path, &_this->rows);
        if (res == 0)
        { //更新列表
            _this->path = new_path;
            _this->file_update_list();
        }
    }
}

/**
 * @description: 点击文件回调
 * @param undefined
 * @return {*}
 */
void folder_browser::file_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    folder_browser *_this = (folder_browser *)lv_event_get_user_data(e);

    if (code != LV_EVENT_CLICKED)
    {
        return;
    }
    char *text = (char *)lv_list_get_btn_text(_this->obj_list, obj);
    LV_LOG_USER("Clicked: %s", text);

    char *tail_name;
    tail_name = strrchr(text, '.');
    if (!tail_name)
    {
        return;
    }
    
    tail_name += 1;
    for (auto item : _this->exec_map)
    {
        if (item.first != tail_name)
        {
            continue;
        }
        if (item.second)
        {
            item.second(_this->path, text);
        }
    }
}

/**
 * @description:
 * @param undefined
 * @param undefined
 * @return {*}
 */
void folder_browser::add_exec(std::string tail_name, folder_browser_exec_func_t exec)
{
    this->exec_map.insert({tail_name, exec});
}
