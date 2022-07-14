project(fts-drivers)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )

file(GLOB_RECURSE SRC_FILES ./*.cpp ./*.c)
file(GLOB_RECURSE HEAD_FILES ./*.h)

#add_library(${PROJECT_NAME} SHARED ${SRC_FILES} HEAD_FILES)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} ${HEAD_FILES})

