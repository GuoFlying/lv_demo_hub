/*
 * @Author: Flying
 * @Date: 2022-05-15 20:44:27
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-11 23:04:56
 * @Description: SSD2XX MI 简易使用
 */

#include "../hw_app.h"
#include "../../../common/c_common.h"
#include <iostream>
using namespace std;
#include <string>
#include "v_wifi_list.h"

#ifdef F_LINUXARM

#include "wifi_widget.h"

lv_obj_t *hw_app_wifi()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    wifi_widget *p = new wifi_widget(parent); //退出会自动释放

    return parent;
}

#else
lv_obj_t *hw_app_wifi()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    v_wifi_list *p = new v_wifi_list(parent);

    {
        v_wifi_list_item item;
        item.singnal = -45;
        item.ssid = "wifi 测试删除列表";
        p->push_back_list(item);
        p->push_back_list(item);
        p->push_back_list(item);
    }
    p->clear();
    {
        v_wifi_list_item item;
        item.singnal = -45;
        item.ssid = "wifi 标题1";
        p->push_back_list(item);
    }

    {
        v_wifi_list_item item;
        item.singnal = -55;
        item.ssid = "wifi 标题2";
        p->set_connect_item(item);
        p->push_back_list(item);
    }

    {
        v_wifi_list_item item;
        item.singnal = -65;
        item.ssid = "wifi 标题3";
        p->push_back_list(item);
    }

    {
        v_wifi_list_item item;
        item.singnal = -75;
        item.ssid = "wifi 标题4";
        p->push_back_list(item);
    }

    p->show();
    return parent;
}

#endif