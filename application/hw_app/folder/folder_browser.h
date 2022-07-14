/*
 * @Author: Flying
 * @Date: 2022-05-21 12:13:15
 * @LastEditors: Flying
 * @LastEditTime: 2022-05-21 16:25:06
 * @Description: 修改文件
 */
#include "../common/hw_app_base.h"
#include <string>
#include <map>

/*列表文件最大值*/
#define FILE_LIST_SIZE_MAX 50
typedef void (*folder_browser_exec_func_t)(std::string, std::string);

class folder_browser : public hw_app_base
{
private:
    lv_obj_t *t_label;
    lv_obj_t *obj_list;
    std::string path;
    f_row_list_t rows;
    std::map<std::string, folder_browser_exec_func_t> exec_map;

    void file_clear_list();

    static void dir_event_handler(lv_event_t *e);
    static void file_event_handler(lv_event_t *e);

public:
    folder_browser(lv_obj_t *parent);
    ~folder_browser();

    void file_update_list();
    void add_exec(std::string tail_name, folder_browser_exec_func_t exec);
};
