cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PREFIX_PATH "D:\\OwnLibrary" ${CMAKE_PREFIX_PATH})
set(CMAKE_TOOLCHAIN_FILE "D:\\Library\\vcpkg\\scripts\\buildsystems\\vcpkg.cmake")

project(charles_algorithm)

find_package(GTest CONFIG REQUIRED)
add_executable(
    ${PROJECT_NAME}_test
    charles_sort_test.cpp
    unit_test.cpp
)

target_link_libraries(${PROJECT_NAME}_test GTest::gtest GTest::gmock)

# this is for export libary for external use
set(CMAKE_INSTALL_PREFIX "D:/OwnLibrary")

add_library(
    ${PROJECT_NAME}
    charles_sort.cpp
)

# 引入要用到的 CMake 模块
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# 基本安装及 Targets 文件的生成
install(TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}-targets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Targets 文件的安装
install(EXPORT ${PROJECT_NAME}-targets
    FILE ${PROJECT_NAME}-targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# Config 文件的导出（与安装？）
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/cmake/config.cmake.in
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# ConfigVersion 文件的导出
write_basic_package_version_file(
    ${PROJECT_NAME}-config-version.cmake
    VERSION 0.1
    COMPATIBILITY AnyNewerVersion
)

# Config 和 ConfigVersion 文件的安装
install(FILES
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake
    ${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)
# install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES "${PROJECT_SOURCE_DIR}/charles_sort.h" DESTINATION include)