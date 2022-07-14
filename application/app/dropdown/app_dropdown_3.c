/*
 * @Author: Flying
 * @Date: 2022-04-28 21:58:12
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 18:48:47
 * @Description: 新建文件
 */
#include "../app.h"

static void event_cb(lv_event_t *e)
{
    lv_obj_t *dropdown = lv_event_get_target(e);
    char buf[64];
    lv_dropdown_get_selected_str(dropdown, buf, sizeof(buf));
    LV_LOG_USER("'%s' is selected", buf);
}

/**
 * Create a menu from a drop-down list and show some drop-down list features and styling
 */
int app_dropdown_3(lv_obj_t *parent)
{
    /*Create a drop down list*/
    lv_obj_t *dropdown = lv_dropdown_create(parent);
    lv_obj_align(dropdown, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_dropdown_set_options(dropdown, "New project\n"
                                      "New file\n"
                                      "Save\n"
                                      "Save as ...\n"
                                      "Open project\n"
                                      "Recent projects\n"
                                      "Preferences\n"
                                      "Exit");

    /*Set a fixed text to display on the button of the drop-down list*/
    lv_dropdown_set_text(dropdown, "Menu");

    /*Use a custom image as down icon and flip it when the list is opened*/
    LV_IMG_DECLARE(app_img_caret_down)
    lv_dropdown_set_symbol(dropdown, &app_img_caret_down);
    lv_obj_set_style_transform_angle(dropdown, 1800, LV_PART_INDICATOR | LV_STATE_CHECKED);

    /*In a menu we don't need to show the last clicked item*/
    lv_dropdown_set_selected_highlight(dropdown, false);

    lv_obj_add_event_cb(dropdown, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    return 0;
}