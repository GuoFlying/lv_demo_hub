/*
 * @Author: Flying
 * @Date: 2021-11-08 17:48:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-08 21:17:59
 * @Description: file content
 */
#pragma once
#include "../../my_conf.h"
#include "../../lvgl/lvgl.h"
#include <map>
#include <string>

class c_font
{
private:
    c_font();
    ~c_font();
    static std::map<int, lv_ft_info_t *> c_icon_map;
    static std::map<int, lv_ft_info_t *> c_map;
    static lv_font_t *get_font_by_name(int type, int size);

public:
    static std::string get_utf8(unsigned short val);

    static lv_font_t *get_font(int size);
    static lv_font_t *get_icon_font(int size);
};
