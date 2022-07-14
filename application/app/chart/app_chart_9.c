/*
 * @Author: Flying
 * @Date: 2022-04-28 21:11:59
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-08 21:51:51
 * @Description: 新建文件
 */
#include "../app.h"

static lv_timer_t *g_timer1 = NULL;
static void parent_del_cb(lv_event_t *e)
{
    if (g_timer1)
    {
        lv_timer_del(g_timer1);
        g_timer1 = NULL;
    }
}

static void add_data(lv_timer_t *t)
{
    lv_obj_t *chart = t->user_data;
    lv_chart_series_t *ser = lv_chart_get_series_next(chart, NULL);

    lv_chart_set_next_value(chart, ser, lv_rand(10, 90));

    uint16_t p = lv_chart_get_point_count(chart);
    uint16_t s = lv_chart_get_x_start_point(chart, ser);
    lv_coord_t *a = lv_chart_get_y_array(chart, ser);

    a[(s + 1) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;
    a[(s + 2) % p] = LV_CHART_POINT_NONE;

    lv_chart_refresh(chart);
}

/**
 * Circular line chart with gap
 */
int app_chart_9(lv_obj_t *parent)
{
    lv_obj_add_event_cb(parent, parent_del_cb, LV_EVENT_DELETE, NULL);

    /*Create a stacked_area_chart.obj*/
    lv_obj_t *chart = lv_chart_create(parent);
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_CIRCULAR);
    lv_obj_set_size(chart, 200, 150);
    lv_obj_center(chart);

    lv_chart_set_point_count(chart, 30);
    lv_chart_series_t *ser = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);
    /*Prefill with data*/
    uint32_t i;
    for (i = 0; i < 30; i++)
    {
        lv_chart_set_next_value(chart, ser, lv_rand(10, 90));
    }

    g_timer1 = lv_timer_create(add_data, 300, chart);
    return 0;
}
