cmake_minimum_required(VERSION 3.16)
set(PACKAGE_NAME gridmap)
project (${PACKAGE_NAME})

set(CMAKE_CXX_STANDARD 14)
set(cetc21 ${CMAKE_SOURCE_DIR}/lib)

find_package(PCL REQUIRED)
find_package(OpenCV REQUIRED)

include_directories( include
        ${OpenCV_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/lib/include/    # lib文件夹中头文件和动态库的搜索路径
)

#编译成可执行文件
# file(GLOB_RECURSE GRIDMAP_SRC "src/*.cpp" "main.cpp")
# add_executable(${PACKAGE_NAME} ${GRIDMAP_SRC})
# target_link_libraries(${PACKAGE_NAME} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

# # 编译成动态库
# file(GLOB_RECURSE GRIDMAP_SRC "src/*.cpp")
# file(GLOB_RECURSE GRIDMAP_INCLUDE "include/gridmapimpl.h")
# set(CMAKE_INSTALL_INCLUDEDIR ${cetc21}/include)
# set(CMAKE_INSTALL_LIBDIR ${cetc21}/${PLATFORM})
# add_library(${PACKAGE_NAME} SHARED  ${GRIDMAP_SRC})
# set_target_properties(${PACKAGE_NAME} PROPERTIES PUBLIC_HEADER "${GRIDMAP_INCLUDE}")
# install(TARGETS ${PACKAGE_NAME} DESTINATION ${CMAKE_INSTALL_LIBDIR}
#         PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PACKAGE_NAME})

# 基于动态库编译成可执行文件
add_executable(gridmap_lib main_lib.cpp)
target_link_libraries(gridmap_lib ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${cetc21}/libgridmap.so)