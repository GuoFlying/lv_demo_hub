project(application)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/libs/freetype2/include
    ${CMAKE_SOURCE_DIR}/libs/ssd20x/include
    )

file(GLOB_RECURSE SRC_FILES ./*.cpp ./*.c)
file(GLOB_RECURSE HEAD_FILES ./*.h)

#add_library(${PROJECT_NAME} SHARED ${SRC_FILES} HEAD_FILES)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEAD_FILES})

