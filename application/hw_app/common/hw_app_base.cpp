/*
 * @Author: Flying
 * @Date: 2022-05-21 12:22:08
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-21 13:46:52
 * @Description: 修改文件
 */
#include "hw_app_base.h"

hw_app_base::hw_app_base(lv_obj_t *parent)
{
    this->parent = parent;
    lv_obj_add_event_cb(parent, parent_del_cb, LV_EVENT_DELETE, this);
}

hw_app_base::~hw_app_base()
{
}

void hw_app_base::parent_del_cb(lv_event_t *e)
{
    hw_app_base *_this = (hw_app_base *)lv_event_get_user_data(e);
    if (_this)
    {
        delete _this;
    }
}
