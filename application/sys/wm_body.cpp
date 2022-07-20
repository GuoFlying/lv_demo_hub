/*
 * @Author: Flying
 * @Date: 2022-03-26 12:51:17
 * @LastEditors: Flying
 * @LastEditTime: 2022-07-20 18:06:10
 * @Description: 新建文件
 */
#include "wm_body.h"
#include "../../lvgl/examples/lv_examples.h"
#include "../../common/c_common.h"

#define CONT_W_MAX (800 * MY_UI_W_ZOOM)
#define CONT_H_MAX (400 * MY_UI_H_ZOOM)

#define ITEM_SPACE_W (40 * MY_UI_W_ZOOM)
#define ITEM_SPACE_H (40 * MY_UI_H_ZOOM)

#define ITEM_W ((CONT_W_MAX - ITEM_SPACE_W * (this->col_max + 1)) / this->col_max)
#define ITEM_H ((CONT_H_MAX - ITEM_SPACE_H * (this->row_max + 1)) / this->row_max)

/**
 * @description:
 * @param {lv_obj_t} *parent
 * @return {*}
 */
wm_body::wm_body(lv_obj_t *parent, wm_body_event_cb_t event_cb, void *cb_arg)
{
    this->sync_page = 0;
    this->sync_index = 0;
    this->item_list.clear();
    this->page_list.clear();
    this->event_cb = event_cb;
    this->cb_arg = cb_arg;
    this->cont = lv_obj_create(parent);
    this->row_max = 2 * MY_UI_H_ZOOM + 0.5; //行数
    this->col_max = 4 * MY_UI_W_ZOOM + 0.5; //列数
    if (this->row_max <= 0)
    { //限制最小，一行两列
        this->row_max = 1;
    }
    if (this->col_max <= 1)
    {
        this->col_max = 2;
    }

    lv_obj_set_size(this->cont, CONT_W_MAX, CONT_H_MAX);
    lv_obj_set_scroll_snap_x(this->cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_flex_flow(this->cont, LV_FLEX_FLOW_ROW);
    lv_obj_align(this->cont, LV_ALIGN_CENTER, 0, -20 * MY_UI_H_ZOOM);
    lv_obj_set_scroll_dir(this->cont, LV_DIR_HOR);
    lv_obj_set_style_radius(this->cont, 0, 0);
    lv_obj_add_flag(this->cont, LV_OBJ_FLAG_SCROLLABLE);   //可滑动
    lv_obj_add_flag(this->cont, LV_OBJ_FLAG_SCROLL_CHAIN); //可滑动
    lv_obj_add_flag(this->cont, LV_OBJ_FLAG_SCROLL_ONE);
    lv_obj_set_style_opa(this->cont, LV_OPA_0, LV_PART_SCROLLBAR); //滑动条隐藏
    lv_obj_set_style_pad_all(this->cont, 0, 0);
    lv_obj_set_style_border_width(this->cont, 0, 0);
    lv_obj_set_style_bg_color(this->cont, lv_color_hex(0xff0000), 0);
    lv_obj_set_style_bg_opa(this->cont, LV_OPA_0, 0);
    lv_obj_add_event_cb(this->cont, wm_body::scroll_event_cb, LV_EVENT_SCROLL_END, this);

    //小图标底图
    lv_style_init(&this->page_style);
    lv_style_set_x(&this->page_style, 0);
    lv_style_set_y(&this->page_style, 0);
    lv_style_set_width(&this->page_style, CONT_W_MAX);
    lv_style_set_height(&this->page_style, CONT_H_MAX);
    lv_style_set_pad_all(&this->page_style, 0);
    lv_style_set_border_width(&this->page_style, 0);
    lv_style_set_radius(&this->page_style, 0);
    lv_style_set_bg_color(&this->page_style, lv_color_hex(0xffff00));
    lv_style_set_bg_opa(&this->page_style, LV_OPA_0);
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
wm_body::~wm_body()
{
}

/**
 * @description: 跳转到哪页
 * @param {int} index
 * @param {lv_anim_enable_t} anim_en
 * @return {*}
 */
void wm_body::select_page(int index, lv_anim_enable_t anim_en)
{
    if (index >= this->page_list.size())
    {
        return;
    }
    lv_obj_t *obj = this->page_list.at(index);
    lv_obj_scroll_to_view(obj, anim_en);
}

/**
 * @description: 获取总共有几页
 * @param {*}
 * @return {*}
 */
int wm_body::get_page_count()
{
    return this->page_list.size();
}

/**
 * @description: 滑动事件
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_body::scroll_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    wm_body *_this = (wm_body *)lv_event_get_user_data(e);
    lv_obj_t *cont = lv_event_get_target(e);

    if (code != LV_EVENT_SCROLL_END)
    {
        return;
    }

    lv_point_t p;
    lv_obj_get_scroll_end(cont, &p);
    _this->sync_page = p.x / (CONT_W_MAX);
    _this->sync_code = CODE_SCROLL;
    // LV_LOG_USER("page = %d\n", index);
    if (_this->event_cb)
    {
        _this->event_cb(_this);
    }
}

/**
 * @description: 获取第几页，如果不存在则创建
 * @param {*} 0开始
 * @return {*}
 */
lv_obj_t *wm_body::get_page(uint8_t index)
{

    if (this->page_list.size() > index)
    {
        return this->page_list.at(index);
    }
    lv_obj_t *obj = lv_obj_create(this->cont);
    lv_obj_add_style(obj, &this->page_style, 0);
    lv_obj_set_style_opa(obj, LV_OPA_0, LV_PART_SCROLLBAR); //滑动条隐藏
    lv_obj_set_style_pad_all(obj, 0, 0);
    lv_obj_set_style_border_width(obj, 0, 0);
    this->page_list.push_back(obj);

    return this->get_page(index);
}

/**
 * @description: 4列2行（800/4=200 ，400/2=200）(上下空出40)
 * @param {*}
 * @return {*}
 */
lv_obj_t *wm_body::add_item(int current_frame, char *lottie_name, char *label_text, bool is_draw_line)
{
    int count = this->item_list.size();
    int page_index = count / (this->row_max * this->col_max);
    int pos = count % (this->row_max * this->col_max); //当前页的坐标
    int col_pos = pos % this->col_max;                 //第几列
    int row_pos = pos / this->col_max;                 //第几行
    lv_obj_t *item_parent = this->get_page(page_index);

    int icon_x = ITEM_SPACE_W + col_pos * (ITEM_W + ITEM_SPACE_W);
    int icon_y = ITEM_SPACE_H + row_pos * (ITEM_H + ITEM_SPACE_H);

    string path = MY_LOTTIE_PATH;
    path += lottie_name;
    lv_obj_t *obj = lv_rlottie_create_from_file(item_parent, ITEM_W, ITEM_H, path.data());
    lv_obj_set_style_bg_color(obj, lv_color_white(), 0);
    lv_rlottie_set_play_mode(obj, LV_RLOTTIE_CTRL_PAUSE);
    if (current_frame < 0)
    {
        lv_rlottie_t *rlottie = (lv_rlottie_t *)obj;
        lv_rlottie_set_current_frame(obj, rlottie->total_frames);
    }
    else
    {
        lv_rlottie_set_current_frame(obj, current_frame);
    }
    lv_obj_set_pos(obj, icon_x, icon_y);

    obj->user_data = (void *)count;

    if (is_draw_line)
    {
        lv_obj_t *line = lv_line_create(item_parent);
        static lv_point_t p[] = {{0, 0}, {(short int)(ITEM_W / 3), 0}};
        lv_line_set_points(line, p, 2);
        lv_obj_set_style_line_width(line, 2 * MY_UI_H_ZOOM, 0);
        lv_obj_set_style_line_color(line, lv_palette_main(LV_PALETTE_RED), 0);
        lv_obj_align_to(line, obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    }

    int label_x = icon_x - ITEM_SPACE_W / this->row_max;
    int label_y = icon_y + ITEM_H;
    lv_obj_t *label = lv_label_create(item_parent);
    // lv_obj_set_style_text_font(label, &lv_font_montserrat_16, 0);
    lv_obj_set_style_text_font(label, c_font::get_font(16 * MY_UI_W_ZOOM), 0);
    lv_obj_set_size(label, ITEM_SPACE_W + ITEM_W, 18 * MY_UI_W_ZOOM);
    // lv_obj_align_to(label, obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 2 * MY_UI_H_ZOOM);
    lv_obj_set_style_pad_top(label, -1 * 16 * MY_UI_H_ZOOM / 5.0 + 0.5, 0);
    lv_obj_set_pos(label, label_x, label_y);
    lv_label_set_long_mode(label, LV_LABEL_LONG_DOT);
    lv_label_set_text(label, label_text);
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);

    this->item_list.push_back(obj);

    lv_obj_add_event_cb(obj, wm_body::item_event_cb, LV_EVENT_PRESSED, this);
    lv_obj_add_event_cb(obj, wm_body::item_event_cb, LV_EVENT_RELEASED, this);
    lv_obj_add_event_cb(obj, wm_body::item_event_cb, LV_EVENT_CLICKED, this);

    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_add_event_cb(obj, wm_body::item_event_cb, LV_EVENT_GESTURE, this);

    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    return obj;
}

/**
 * @description: 点击事件+动效
 * @param {lv_event_t} *e
 * @return {*}
 */
void wm_body::item_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    wm_body *_this = (wm_body *)lv_event_get_user_data(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_GESTURE)
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());

        bool success = false;
        switch (dir)
        {
        case LV_DIR_LEFT:
            // printf("LV_DIR_LEFT\r\n");
            break;
        case LV_DIR_RIGHT:
            // printf("LV_DIR_RIGHT\r\n");
            break;
        case LV_DIR_TOP:
            _this->sync_index = *((int *)&obj->user_data);
            _this->sync_code = CODE_GESTURE_UP;
            if (_this->event_cb)
            {
                _this->event_cb(_this);
            }
            lv_obj_add_flag(obj, LV_OBJ_FLAG_USER_2);
            break;
        case LV_DIR_BOTTOM:
            // printf("LV_DIR_BOTTOM\r\n");
            break;
        default:
            break;
        }
        return;
    }

    if (code == LV_EVENT_PRESSED)
    {
        lv_rlottie_set_play_mode(obj, LV_RLOTTIE_CTRL_LOOP);
        lv_obj_set_style_bg_opa(obj, LV_OPA_40, 0);
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_USER_2);
        return;
    }
    if (code == LV_EVENT_RELEASED)
    {
        lv_rlottie_set_play_mode(obj, LV_RLOTTIE_CTRL_PAUSE);
        lv_obj_set_style_bg_opa(obj, LV_OPA_0, 0);
        return;
    }

    if (code != LV_EVENT_CLICKED)
    {
        return;
    }

    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_USER_2))
    {
        return;
    }

    _this->sync_index = *((int *)&obj->user_data);
    _this->sync_code = CODE_CLICKED;
    if (_this->event_cb)
    {
        _this->event_cb(_this);
    }
    // LV_LOG_USER("CLICKED %d", index);
}
