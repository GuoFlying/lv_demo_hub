/*
 * @Author: Flying
 * @Date: 2022-03-27 14:53:51
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-10 15:08:24
 * @Description: 标题说明
 * U: 完整DEMO，但不能操作实际设备
 * W：widget；lvgl按组件分类的demo
 * S：LVGL 功能性DEMO（内涵多种widget组合），更多的是为学习如何使用API，而非看效果
 */
#pragma once
#include "../../lvgl/lvgl.h"
#include "../../lv_lib_100ask/lv_lib_100ask.h"
#include "../../my_conf.h"
#ifdef __cplusplus
extern "C"
{
#endif

    typedef lv_obj_t *(*app_fun_t)();

#include "common/app_common.h"
#include "common/v_font.h"

    lv_obj_t *wm_demo_widgets();
    lv_obj_t *printer_3d_init();
    lv_obj_t *app_mini3d();
    lv_obj_t *app_music();
    lv_obj_t *app_stress();
    lv_obj_t *app_benchmark();
    lv_obj_t *app_games();
    lv_obj_t *app_other();

    lv_obj_t *app_style();
    lv_obj_t *app_scroll();
    lv_obj_t *app_get_started();
    lv_obj_t *app_anim();
    lv_obj_t *app_flex();
    lv_obj_t *app_grid();

    lv_obj_t *app_animimg();
    lv_obj_t *app_arc();
    lv_obj_t *app_bar();
    lv_obj_t *app_btnmatrix();
    lv_obj_t *app_calendar();
    lv_obj_t *app_canvas();
    lv_obj_t *app_chart();
    lv_obj_t *app_checkbox();
    lv_obj_t *app_colorwheel();
    lv_obj_t *app_dropdown();
    lv_obj_t *app_img();
    lv_obj_t *app_imgbtn();
    lv_obj_t *app_keyboard();
    lv_obj_t *app_label();
    lv_obj_t *app_led();
    lv_obj_t *app_line();
    lv_obj_t *app_list();
    lv_obj_t *app_menu();
    lv_obj_t *app_meter();
    lv_obj_t *app_msgbox();
    lv_obj_t *app_obj();
    lv_obj_t *app_roller();
    lv_obj_t *app_slider();
    lv_obj_t *app_span();
    lv_obj_t *app_spinbox();
    lv_obj_t *app_spinner();
    lv_obj_t *app_switch();
    lv_obj_t *app_table();
    lv_obj_t *app_tabview();
    lv_obj_t *app_textarea();
    lv_obj_t *app_tileview();
    lv_obj_t *app_win();
#define _APPS_FUN_LIST                                                  \
    {40, "widget.json", "U:窗体部件", wm_demo_widgets},                 \
        {10, "printer.json", "U:3D打印机", printer_3d_init},            \
        {20, "music.json", "U:音乐播放器", app_music},                  \
        {20, "stress.json", "U:压力测试", app_stress},                  \
        {120, "benchmark.json", "U:基准测试", app_benchmark},           \
        {120, "games.json", "U:游戏", app_games},                       \
        {10, "other.json", "U:其他", app_other},                        \
        {30, "style.json", "S:style功能", app_style},                   \
        {30, "scroll.json", "S:scroll功能", app_scroll},                \
        {30, "get_started.json", "S:get_started功能", app_get_started}, \
        {30, "anim.json", "S:anim功能", app_anim},                      \
        {30, "flex.json", "S:flex功能", app_flex},                      \
        {30, "grid.json", "S:grid功能", app_grid},                      \
        {10, "animimg.json", "W:animimg组件", app_animimg},             \
        {10, "arc.json", "W:arc组件", app_arc},                         \
        {10, "bar.json", "W:bar组件", app_bar},                         \
        {0, "btnmatrix.json", "W:btnmatrix组件", app_btnmatrix},        \
        {20, "calendar.json", "W:calendar组件", app_calendar},          \
        {20, "canvas.json", "W:canvas组件", app_canvas},                \
        {20, "chart.json", "W:chart组件", app_chart},                   \
        {20, "checkbox.json", "W:checkbox组件", app_checkbox},          \
        {20, "colorwheel.json", "W:colorwheel组件", app_colorwheel},    \
        {20, "dropdown.json", "W:dropdown组件", app_dropdown},          \
        {20, "img.json", "W:img组件", app_img},                         \
        {20, "imgbtn.json", "W:imgbtn组件", app_imgbtn},                \
        {20, "keyboard.json", "W:keyboard组件", app_keyboard},          \
        {0, "label.json", "W:label组件", app_label},                    \
        {0, "led.json", "W:led组件", app_led},                          \
        {0, "line.json", "W:line组件", app_line},                       \
        {30, "list.json", "W:list组件", app_list},                      \
        {0, "menu.json", "W:menu组件", app_menu},                       \
        {0, "meter.json", "W:meter组件", app_meter},                    \
        {30, "msgbox.json", "W:msgbox组件", app_msgbox},                \
        {100, "obj.json", "W:obj组件", app_obj},                        \
        {30, "roller.json", "W:roller组件", app_roller},                \
        {30, "slider.json", "W:slider组件", app_slider},                \
        {30, "span.json", "W:span组件", app_span},                      \
        {30, "spinbox.json", "W:spinbox组件", app_spinbox},             \
        {30, "spinner.json", "W:spinner组件", app_spinner},             \
        {30, "switch.json", "W:switch组件", app_switch},                \
        {30, "table.json", "W:table组件", app_table},                   \
        {30, "tabview.json", "W:tabview组件", app_tabview},             \
        {30, "textarea.json", "W:textarea组件", app_textarea},          \
        {30, "tileview.json", "W:tileview组件", app_tileview},          \
        {30, "win.json", "W:win组件", app_win},

#ifdef __cplusplus
}
#endif
