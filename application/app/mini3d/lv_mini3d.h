/*
 * @Author: Flying
 * @Date: 2022-04-29 14:59:51
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-29 22:46:16
 * @Description: 新建文件
 */

#ifndef LV_MINI3D_H
#define LV_MINI3D_H

#ifdef __cplusplus
extern "C"
{
#endif

/*********************
 *      INCLUDES
 *********************/
#include "../app.h"

    /*********************
     *      DEFINES
     *********************/

    /**********************
     *      TYPEDEFS
     **********************/
    typedef enum
    {
        LV_RENDER_STATE_WIREFRAME = 1 << 0, // 渲染线框
        LV_RENDER_STATE_TEXTURE = 1 << 1,   // 渲染纹理
        LV_RENDER_STATE_COLOR = 1 << 2,     // 渲染颜色
    } lv_mini3d_render_t;

    /** definition in lottieanimation_capi.c */
    struct Lottie_Animation_S;
    typedef struct
    {
        lv_img_t img_ext;    //继承img时必须存在
        lv_img_dsc_t imgdsc; //图像数据
        void *device;        //驱动地址
        float alpha;
        float pos;
        int dest_render;
        float dest_alpha;
        float dest_pos;
        uint32_t *allocated_buf;
        size_t allocated_buffer_size;
        lv_timer_t *task;

    } lv_mini3d_t;

    extern const lv_obj_class_t lv_mini3d_class;

    /**********************
     * GLOBAL PROTOTYPES
     **********************/

    lv_obj_t *lv_mini3d_create(lv_obj_t *parent, lv_coord_t width, lv_coord_t height);

    void lv_mini3d_set_render(lv_obj_t *mini3d, int render);
    void lv_mini3d_set_alpha(lv_obj_t *mini3d, float alpha);
    void lv_mini3d_set_pos(lv_obj_t *mini3d, float pos);
    /**********************
     *      MACROS
     **********************/

#endif /*LV_USE_mini3d*/

#ifdef __cplusplus
} /* extern "C" */
#endif
