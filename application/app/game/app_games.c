/*
 * @Author: Flying
 * @Date: 2022-05-02 18:29:26
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-15 11:18:09
 * @Description: 新建文件
 */
#include "../app.h"
#include "f_game_2048.h"
#include "f_game_snake.h"
#include "f_game_tetris.h"

int game_100ask(lv_obj_t *parent);

lv_obj_t *app_games()
{
    lv_obj_t *parent = lv_obj_create(NULL);
    lv_obj_t *list1 = app_common_obj_create("games example", parent);
    app_common_obj_add_item(list1, "2048", lv_f_game_2048);
    app_common_obj_add_item(list1, "贪吃蛇", lv_f_game_snake);
    app_common_obj_add_item(list1, "俄罗斯方块", f_game_tetris);
    app_common_obj_add_item(list1, "100ask:消除相同", game_100ask);
    return parent;
}
