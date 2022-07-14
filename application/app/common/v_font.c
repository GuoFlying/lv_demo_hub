/*
 * @Author: Flying
 * @Date: 2022-04-24 22:25:44
 * @LastEditors: Flying
 * @LastEditTime: 2022-04-24 22:34:09
 * @Description: 新建文件
 */
#include "v_font.h"
#include "list.h"

typedef struct v_font_node_t_
{
    int size;
    lv_ft_info_t *ft_font;
} v_font_node_t;

static list_t *font_list = NULL;
static lv_font_t *v_font_get_create(int size);

static void v_font_once_init()
{
    if (font_list)
    {
        return;
    }
    font_list = list_new();
    if (!font_list)
    {
        return;
    }
}

static lv_font_t *v_font_get_exist(int size)
{

    list_iterator_t *it = list_iterator_new(font_list, LIST_HEAD);
    list_node_t *node;

    if (!it)
    {
        return NULL;
    }

    while (node = list_iterator_next(it))
    {
        v_font_node_t *font_node = (v_font_node_t *)node->val;

        if (!font_node)
        {
            continue;
        }

        if (font_node->size != size)
        {
            continue;
        }

        if (font_node->ft_font)
        {
            return font_node->ft_font->font;
        }
    }

    return NULL;
}

static lv_font_t *v_font_get_create(int size)
{
    //不存在则创建

    v_font_node_t *node = malloc(sizeof(v_font_node_t));

    if (!node)
    {
        return NULL;
    }

    lv_ft_info_t *info = malloc(sizeof(lv_ft_info_t));

    if (!info)
    {
        free(node);
        return NULL;
    }
    else
    {
        memset(info, 0, sizeof(*info));
    }

    info->name = MY_FONT_NAME;
    info->weight = size;
    info->style = FT_FONT_STYLE_NORMAL;
    lv_ft_font_init(info);

    node->ft_font = info;
    node->size = size;

    list_rpush(font_list, list_node_new((void *)node));

    return info->font;
}

lv_font_t *get_lv_font_by_size(int size)
{

    v_font_once_init();

    //避免恶意字体
    if (size <= 0 || size >= 1000)
    {
        return NULL;
    }

    //已经存在
    lv_font_t *tmp_font = v_font_get_exist(size);
    if (tmp_font)
    {
        return tmp_font;
    }
    return v_font_get_create(size);
}
