# 生成静态库通用宏
macro(add_static_lib _name _path)

    file(GLOB_RECURSE SRC_FILES   "${_path}/*.c")
    file(GLOB_RECURSE HEAD_FILES  "${_path}/*.h"  "./*.h"  )
    add_library(${_name} STATIC ${SRC_FILES} ${HEAD_FILES})

    #后面所有参数添加连接库
    foreach(_lib_item ${ARGN})
        target_link_libraries(${_name} ${_lib_item})
    endforeach(_lib_item)

endmacro(add_static_lib)
