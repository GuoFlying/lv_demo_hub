/*
 * @Author: Flying
 * @Date: 2022-03-23 21:12:02
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-19 22:37:49
 * @Description: 新建文件
 */
#include "wm_application.h"

typedef struct apps_func_
{
    int current_frame;
    const char *lottie_name;
    const char *label;
    app_fun_t func;
} apps_func_t;

static apps_func_t apps[] = {
    _HW_APPS_FUN_LIST
        _APPS_FUN_LIST};

#define APPS_SIZE (sizeof(apps) / sizeof(apps[0]))

wm_application::wm_application()
{
    // disp 图目前有bug
    //  lv_disp_set_bg_image(lv_disp_get_default(), MY_PNG_PATH "bg.png");
    this->app_home = NULL;
    this->is_app = false;
    this->is_theme_dark = false;

    // this->app_home = lv_obj_create(NULL);
    // lv_obj_remove_style_all(this->app_home);
    // lv_obj_set_style_bg_opa(this->app_home, LV_OPA_0, 0);
    // lv_obj_set_style_bg_color(this->app_home, lv_color_hex(0x000000), 0);
    // lv_obj_set_style_bg_img_src(this->app_home, MY_PNG_PATH "bg.png", 0);
    // lv_obj_set_style_bg_img_opa(this->app_home, LV_OPA_100, 0);
    // lv_obj_set_style_bg_img_tiled(this->app_home, true, 0);
    lv_img_header_t header;
    if (lv_img_decoder_get_info(MY_PNG_PATH "bg.png", &header) != LV_RES_OK)
    {
        header.w = MY_UI_W_MAX;
        header.h = MY_UI_H_MAX;
    }

    this->app_home = lv_img_create(NULL);
    lv_obj_remove_style_all(this->app_home);
    lv_img_set_size_mode(this->app_home, LV_IMG_SIZE_MODE_REAL);
    lv_img_set_src(this->app_home, MY_PNG_PATH "bg.png");
    lv_obj_set_size(this->app_home, MY_UI_W_MAX, MY_UI_H_MAX);
    lv_obj_clear_flag(this->app_home, LV_OBJ_FLAG_SCROLLABLE);

    int zoom_val = 256;
    if (MY_UI_H_ZOOM > MY_UI_W_ZOOM)
    {
        zoom_val = LV_IMG_ZOOM_NONE * MY_UI_H_MAX / header.h;
    }
    else
    {
        zoom_val = LV_IMG_ZOOM_NONE * MY_UI_W_MAX / header.w;
    }
    lv_img_set_zoom(this->app_home, zoom_val);
    LV_LOG_USER("%d", zoom_val);
    lv_obj_center(this->app_home);

    this->home_btn = new wm_home_btn(wm_application::home_btn_event_cb, this);
    this->body = new wm_body(this->app_home, wm_application::body_event_cb, this);

    for (auto item : apps)
    {
        this->body->add_item(item.current_frame, (char *)item.lottie_name, (char *)item.label);
    }

    this->footer = new wm_footer(this->app_home, this->body->get_page_count(),
                                 wm_application::footer_event_cb, this);
    this->footer->set_bg_color(lv_color_hex(0xffffff));

    this->head = new wm_head(this->app_home);

    this->settings = new wm_settings(lv_layer_top());
    this->explain = new wm_explain(lv_layer_top());

    lv_disp_load_scr(this->app_home);
}

wm_application::~wm_application()
{
}

/**
 * @description: 20 ms 执行一次
 * @param {*}
 * @return {*}
 */
void wm_application::run()
{
}

/**
 * @description:
 * @param {int} index
 * @return {*}
 */
void wm_application::body_event_cb(wm_body *body)
{
    wm_application *_this = (wm_application *)body->get_cb_arg();
    if (!_this)
    {
        return;
    }
    wm_body::CODE_E code = body->get_sync_code();
    switch (code)
    {
    case wm_body::CODE_SCROLL:
        _this->footer->select(body->get_sync_page());
        break;
    case wm_body::CODE_CLICKED:
        if (body->get_sync_index() < APPS_SIZE)
        {
            lv_obj_t *app = apps[body->get_sync_index()].func();
            LV_ASSERT(app);
            _this->show_app(app);
        }
        break;
    case wm_body::CODE_GESTURE_UP:
        LV_LOG_USER("");
        break;
    default:
        break;
    }
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void wm_application::show_app(lv_obj_t *cont)
{
    static int anim_type = LV_SCR_LOAD_ANIM_OVER_LEFT;

    this->is_app = true;

    lv_scr_load_anim(cont, (lv_scr_load_anim_t)anim_type, 200, 0, false);
    if (++anim_type >= LV_SCR_LOAD_ANIM_MOVE_BOTTOM)
    {
        anim_type = LV_SCR_LOAD_ANIM_OVER_LEFT;
    }
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
bool wm_application::del_app()
{
    static int anim_type = LV_SCR_LOAD_ANIM_OVER_LEFT;
    if (!this->is_app)
    {
        return false;
    }
    this->is_app = false;
    lv_scr_load_anim(this->app_home, (lv_scr_load_anim_t)anim_type, 200, 0, true);

    if (++anim_type >= LV_SCR_LOAD_ANIM_MOVE_BOTTOM)
    {
        anim_type = LV_SCR_LOAD_ANIM_OVER_LEFT;
    }
    return true;
}

/**
 * @description:
 * @param {int} code
 * @param {void} *cb_arg
 * @return {*}
 */
void wm_application::home_btn_event_cb(int code, void *cb_arg)
{
    wm_application *_this = (wm_application *)cb_arg;
    if (!_this)
    {
        return;
    }
    bool is;
    switch (code)
    {
    case HOME_BTN_CODE_HOME:
        _this->head->reset();
        is = _this->del_app();
        if (_this->settings->exit())
        {
            is = true;
        }
        if (_this->explain->exit())
        {
            is = true;
        }
        if (!is)
        {
            _this->body->select_page(0);
        }
        break;
    case HOME_BTN_CODE_SETTINGS:
        _this->explain->exit();
        is = _this->settings->exit();
        if (is)
        {
            break;
        }
        _this->settings->show();
        break;
    case HOME_BTN_CODE_THEME:
        _this->change_theme();
        break;
    case HOME_BTN_CODE_EXPLAIN:

        _this->settings->exit();
        is = _this->explain->exit();
        if (is)
        {
            break;
        }
        _this->explain->show();
        break;
    default:
        break;
    }
}

/**
 * @description:
 * @param {int} index
 * @return {*}
 */
void wm_application::footer_event_cb(int index, void *cb_arg)
{
    // LV_LOG_USER("%d", index);
    wm_application *_this = (wm_application *)cb_arg;
    if (!_this)
    {
        return;
    }
    _this->body->select_page(index);
}

/**
 * @description: 主题切换
 * @param {*}
 * @return {*}
 */
void wm_application::change_theme()
{
    is_theme_dark = !is_theme_dark;
    if (is_theme_dark)
    {
        // lv_obj_set_style_bg_img_src(this->app_home, MY_PNG_PATH "dark_bg.png", 0);
        lv_img_set_src(this->app_home, MY_PNG_PATH "dark_bg.png");
        lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                              1, LV_FONT_DEFAULT);
        this->footer->set_bg_color(lv_color_hex(0x6f6f6f));
    }
    else
    {
        lv_img_set_src(this->app_home, MY_PNG_PATH "bg.png");
        // lv_obj_set_style_bg_img_src(this->app_home, MY_PNG_PATH "bg.png", 0);
        lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                              0, LV_FONT_DEFAULT);
        this->footer->set_bg_color(lv_color_hex(0xffffff));
    }
}
