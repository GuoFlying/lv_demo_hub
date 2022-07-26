/*
 * @Author: Flying
 * @Date: 2022-05-01 22:35:37
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-01 22:35:59
 * @Description: 新建文件
 */
#include "../app.h"

static void drag_event_handler(lv_event_t *e)
{
    lv_obj_t *obj = lv_event_get_target(e);

    lv_indev_t *indev = lv_indev_get_act();
    if (indev == NULL)
        return;

    lv_point_t vect;
    lv_indev_get_vect(indev, &vect);

    lv_coord_t x = lv_obj_get_x(obj) + vect.x;
    lv_coord_t y = lv_obj_get_y(obj) + vect.y;
    lv_obj_set_pos(obj, x, y);
}

/**
 * Make an object dragable.
 */
int app_obj_2(lv_obj_t *parent)
{
    lv_obj_t *obj;
    obj = lv_obj_create(parent);
    lv_obj_set_size(obj, 150, 100);
    lv_obj_add_event_cb(obj, drag_event_handler, LV_EVENT_PRESSING, NULL);

    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, "Drag me");
    lv_obj_center(label);
    return 0;
}
