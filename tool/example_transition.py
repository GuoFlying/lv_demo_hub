'''
Author: Flying
Date: 2022-05-01 20:45:12
LastEditors: Flying
LastEditTime: 2022-05-02 16:30:55
Description: windos 脚本:只能替换大部分内容，一些内容需要手动修改
'''

# cofing:utf8
import os
import re

app = "scroll"
path = r"g:\\workspace\\lv_demo_hub\\lv_demo_hub\\application\\app\\"+app+"\\"
app_name = "app_" + app


def reset():
    filelist = os.listdir(path)
    for files in filelist:
        filename = os.path.splitext(files)[0]  # 名称
        filetype = os.path.splitext(files)[1]  # 扩增名
        filepath = path + filename + filetype
        newfilepath = path + filename.replace("lv_example_", "app_") + filetype
        if filetype != ".c":
            os.remove(filepath)  # 删除非.c文件
        else:
            os.rename(filepath, newfilepath)
            alter(newfilepath)
    # 创建demo文件
    filelist = os.listdir(path)
    for files in filelist:  # 移除demo文件干扰
        if app_name + ".c" in files:
            # filelist.remove(files)
            return  # 已经存在则不再处理，避免覆盖

    with open(path + app_name + ".c", "w", encoding="utf-8") as f1:
        f1.write('#include "../app.h"\n')
        for files in filelist:
            filename = os.path.splitext(files)[0]
            f1.write('int ' + filename + '(lv_obj_t *parent);\n')
        f1.write('lv_obj_t *'+app_name+'()\n')
        f1.write('{\n')
        f1.write('    lv_obj_t *parent = lv_obj_create(NULL);\n')
        f1.write('    lv_obj_t *list1 = app_common_obj_create("' +
                 app + ' example", parent);\n')
        for files in filelist:
            filename = os.path.splitext(files)[0]
            f1.write('    app_common_obj_add_item(list1, "title_' +
                     filename + '", ' + filename + ');\n')
        f1.write('    return parent;\n')
        f1.write('}\n')


def alter(file):
    with open(file, "r", encoding="utf-8") as f1, open("%s.bak" % file, "w", encoding="utf-8") as f2:
        for line in f1:
            if "#if " in line:
                continue
            if "#endif" in line:
                continue
            line = line.replace('../lv_examples.h', "../app.h")
            line = line.replace('lv_scr_act()', "parent")

            if "void lv_example_" in line:  # 替换文件头
                line = line.replace('void lv_example_', "int app_")
                line = line.replace('(void)', "(lv_obj_t *parent)")
            f2.write(line)
    os.remove(file)  # 删除原文件
    os.rename("%s.bak" % file, file)


if __name__ == '__main__':
    reset()
