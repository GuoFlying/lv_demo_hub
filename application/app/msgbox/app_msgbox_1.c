/*
 * @Author: Flying
 * @Date: 2022-05-01 22:31:45
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:32:20
 * @Description: 新建文件
 */
#include "../app.h"

static void event_cb(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_current_target(e);
    LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
}

int app_msgbox_1(lv_obj_t *parent)
{
    static const char *btns[] = {"Apply", "Close", ""};

    lv_obj_t *mbox1 = lv_msgbox_create(NULL, "Hello", "This is a message box with two buttons.", btns, true);
    lv_obj_add_event_cb(mbox1, event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_center(mbox1);
    return 0;
}
