/*
 * @Author: Flying
 * @Date: 2022-05-01 23:09:46
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 23:10:12
 * @Description: 新建文件
 */
#include "../app.h"
static void event_handler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", (int)lv_obj_get_index(obj));
}

lv_obj_t *app_win()
{
    lv_obj_t *parent = lv_obj_create(NULL);

    lv_obj_t *win = lv_win_create(parent, 40);
    lv_obj_set_style_bg_color(win, lv_color_hex(0x000000), 0);
    lv_obj_t *btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_LEFT, 40);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    lv_win_add_title(win, "A title");

    btn = lv_win_add_btn(win, LV_SYMBOL_RIGHT, 40);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 60);
    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

    lv_obj_t *cont = lv_win_get_content(win); /*Content can be added here*/
    lv_obj_t *label = lv_label_create(cont);
    lv_label_set_text(label, "This is\n"
                             "a pretty\n"
                             "long text\n"
                             "to see how\n"
                             "the window\n"
                             "becomes\n"
                             "scrollable.\n"
                             "\n"
                             "\n"
                             "Some more\n"
                             "text to be\n"
                             "sure it\n"
                             "overflows. :)");

    return parent;
}