/*
 * @Author: Flying
 * @Date: 2022-05-01 18:21:42
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-10 14:56:25
 * @Description: 新建文件
 */

#include "../app.h"
int app_keyboard_1(lv_obj_t *parent);
int app_keyboard_2(lv_obj_t *parent);
int app_ime_pinyin_1(lv_obj_t *parent);
int app_ime_pinyin_2(lv_obj_t *parent);

lv_obj_t *app_keyboard()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("keyboard example", parent);
    app_common_obj_add_item(list1, "官方英文键盘", app_keyboard_1);
    app_common_obj_add_item(list1, "全拼简单中文键盘", app_keyboard_2);
    app_common_obj_add_item(list1, "LVGL官方中文键盘", app_ime_pinyin_1);
    // app_common_obj_add_item(list1, "LVGL官方中文键盘", app_ime_pinyin_2); //windows 断言，LVGL core存在问题，异常未排查
    return parent;
}
