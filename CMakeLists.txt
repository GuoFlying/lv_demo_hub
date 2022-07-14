#cmake 入口
cmake_minimum_required (VERSION 3.10)
project ("lv_demo_hub")

# set(CMAKE_CXX_FLAGS "-O3 -g0 -Wall -Wshadow -Wundef -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare ${CMAKE_CXX_FLAGS}")
# set(CMAKE_C_FLAGS "-O3 -g0 -Wall -Wshadow -Wundef -Wmissing-prototypes -Wextra -Wno-unused-function -Wno-error=strict-prototypes -Wpointer-arith -fno-strict-aliasing -Wno-error=cpp -Wuninitialized -Wmaybe-uninitialized -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wformat-security -Wno-ignored-qualifiers -Wno-error=pedantic -Wno-sign-compare -Wno-error=missing-prototypes -Wdouble-promotion -Wclobbered -Wdeprecated -Wempty-body -Wtype-limits -Wshift-negative-value -Wstack-usage=2048 -Wno-unused-value -Wno-unused-parameter -Wno-missing-field-initializers -Wuninitialized -Wmaybe-uninitialized -Wall -Wextra -Wno-unused-parameter -Wno-missing-field-initializers -Wtype-limits -Wsizeof-pointer-memaccess -Wno-format-nonliteral -Wpointer-arith -Wno-cast-qual -Wunreachable-code -Wno-switch-default -Wreturn-type -Wmultichar -Wno-discarded-qualifiers -Wformat-security -Wno-ignored-qualifiers -Wno-sign-compare ${CMAKE_C_FLAGS}")

set(CMAKE_CXX_FLAGS "-O3  ${CMAKE_CXX_FLAGS}")
set(CMAKE_C_FLAGS "-O3  ${CMAKE_C_FLAGS}")

# if(FLYING_PLATFORM STREQUAL "ubuntu")
#     set(CMAKE_CXX_FLAGS "-m32  ${CMAKE_CXX_FLAGS}")
#     set(CMAKE_C_FLAGS "-m32  ${CMAKE_C_FLAGS}")
# endif()

set(OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build_out)
# set(LIBRARY_OUTPUT_PATH    ${OUTPUT_PATH}/lib)
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib) #目前中间文件为.a没用到
set(EXECUTABLE_OUTPUT_PATH ${OUTPUT_PATH})

include(${CMAKE_CURRENT_LIST_DIR}/cmake_conf/common.cmake)

if(FLYING_PLATFORM STREQUAL "linuxarm")
    message("${Green} 当前使用demo适用于：linuxarm ${ColourReset}")
    set(MY_PLATFORM arm)
    add_definitions(-DF_LINUXARM)

elseif(FLYING_PLATFORM STREQUAL "ubuntu")
    # eg：cmake -D CMAKE_TOOLCHAIN_FILE=toolchain_mp157.cmake -D CHIP=mp157 ..
    set(MY_PLATFORM ubuntu)
    add_definitions(-DF_UBUNTU)
    message("${Green} 当前使用demo适用于：ubuntu ${ColourReset}")

else()
    message("${Red} 请指定编译目标。eg：cmake -D CMAKE_TOOLCHAIN_FILE=./cmake_conf/toolchain.cmake -D FLYING_PLATFORM=linuxarm .. ${ColourReset}" )
    message(FATAL_ERROR)
endif()


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/libs/freetype2/include
    ${CMAKE_SOURCE_DIR}/libs/rlottie/include
    )
    
link_directories(${CMAKE_SOURCE_DIR}/libs/freetype2/${MY_PLATFORM})
link_directories(${CMAKE_SOURCE_DIR}/libs/rlottie/${MY_PLATFORM})


add_static_lib(lvgl lvgl)
add_static_lib(my_drivers my_drivers)
add_static_lib(lv_lib_100ask lv_lib_100ask)
add_static_lib(my_lib my_lib)

add_subdirectory(application)
add_subdirectory(common)



if(FLYING_PLATFORM STREQUAL "linuxarm")

    link_directories(${CMAKE_SOURCE_DIR}/libs/ssd20x/ex_libs/dynamic)
    link_directories(${CMAKE_SOURCE_DIR}/libs/ssd20x/mi_libs/dynamic)

    add_executable (${PROJECT_NAME} "main.cpp" )

    target_link_libraries(
        ${PROJECT_NAME}
        application my_drivers lv_lib_100ask common my_lib lvgl
         "-lpthread"
        "-ldl -lfreetype -lrlottie -lmi_common -lmi_sys -lmi_wlan -lcjson"
        )
      

elseif(FLYING_PLATFORM STREQUAL "ubuntu")

    add_executable (${PROJECT_NAME} "main.cpp" )

    target_link_libraries(
        ${PROJECT_NAME}
        application my_drivers lv_lib_100ask common my_lib lvgl
        "-lpthread"
        "-lz -lfreetype -ldl -lSDL2 -lrlottie"
        )

else()
    message("${Red} 请指定编译目标。eg：cmake -D CMAKE_TOOLCHAIN_FILE=toolchain.cmake -D FLYING_PLATFORM="linuxarm" .. ${ColourReset}" )
    message(FATAL_ERROR)
endif()

add_custom_target(
    cp-resource ALL
COMMAND 
    ${CMAKE_COMMAND} -E make_directory ${OUTPUT_PATH}/resource/
COMMAND 
    cp -rf ${CMAKE_CURRENT_SOURCE_DIR}/resource/* ${OUTPUT_PATH}/resource/
COMMAND 
    ${CMAKE_COMMAND} -E make_directory ${OUTPUT_PATH}/resource/lib
COMMAND 
    cp -rf ${CMAKE_CURRENT_SOURCE_DIR}/libs/freetype2/${MY_PLATFORM}/*.so* ${OUTPUT_PATH}/resource/lib
COMMAND 
    cp -rf ${CMAKE_CURRENT_SOURCE_DIR}/libs/rlottie/${MY_PLATFORM}/*.so* ${OUTPUT_PATH}/resource/lib
COMMAND 
    cp -rf ${CMAKE_CURRENT_SOURCE_DIR}/arm_run.sh* ${OUTPUT_PATH}/run.sh
COMMAND 
    chmod a+x ${OUTPUT_PATH}/run.sh
COMMENT
    "CP-RESOURCE ALL"
)