/*
 * @Author: Flying
 * @Date: 2021-10-27 11:28:18
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-21 14:51:19
 * @Description: file content
 */
#ifndef _FILE_ROVER_H_
#define _FILE_ROVER_H_

#include <sys/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define FILE_PATH_MAX 1024 /* # chars in a path name including nul */

typedef struct f_row_t_
{
    char *name;
    off_t size;
    mode_t mode;
    int islink;
    int marked;
} f_row_t;

typedef struct f_row_list_t_
{
    f_row_t *row;
    int nfiles;
} f_row_list_t;

void file_rover_test(void);

//*row非NULL时，会进行释放
//返回 0成功：其他失败

//获取当前应用执行路径以及文件列表
int file_rover_get_row_cwd(char *path, f_row_list_t *rows);
//传入指定地址获取文件列表
int file_rover_get_row_down(const char *path, f_row_list_t *rows);
//传入指定地址的上一级路径(..)病获取文件列表
int file_rover_get_row_up(const char *path, char *dest_path, f_row_list_t *rows);
//内存释放
int file_rover_free(f_row_list_t *rows);

//判断是否为文件夹
//0 ：非文件夹，其他文件夹
int file_rover_is_dir(mode_t mide);
int file_rover_get_size_buf(char *buff,  off_t size);

#ifdef __cplusplus
}
#endif

#endif
