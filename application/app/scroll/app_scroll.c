/*
 * @Author: Flying
 * @Date: 2022-05-02 16:31:33
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-02 16:39:10
 * @Description: 新建文件
 */
#include "../app.h"
int app_scroll_1(lv_obj_t *parent);
int app_scroll_2(lv_obj_t *parent);
int app_scroll_3(lv_obj_t *parent);
int app_scroll_4(lv_obj_t *parent);
int app_scroll_5(lv_obj_t *parent);
int app_scroll_6(lv_obj_t *parent);
lv_obj_t *app_scroll()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("scroll example", parent);
    app_common_obj_add_item(list1, "多层嵌套 scroll", app_scroll_1);
    app_common_obj_add_item(list1, "横向 scroll", app_scroll_2);
    app_common_obj_add_item(list1, "纵向可添加item", app_scroll_3);
    app_common_obj_add_item(list1, "文本框超范围", app_scroll_4);
    app_common_obj_add_item(list1, "阿拉伯语超范围（右对齐）", app_scroll_5);
    app_common_obj_add_item(list1, "圆形滑动效果 scroll", app_scroll_6);
    return parent;
}
