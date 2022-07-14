/*
 * @Author: Flying
 * @Date: 2022-05-21 12:22:18
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-21 13:58:16
 * @Description: 修改文件
 */
#pragma once
#include "../hw_app.h"
#include "../../../common/c_common.h"

class hw_app_base
{
private:
    static void parent_del_cb(lv_event_t *e);

protected:
    lv_obj_t *parent;

public:
    hw_app_base(lv_obj_t *parent);
    virtual ~hw_app_base();
};
