cmake_minimum_required(VERSION 3.16)

project(QIconKitExamples LANGUAGES CXX)

# 设置CMake变量
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 查找Qt依赖
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 收集所有源文件
file(GLOB_RECURSE EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# 单独添加主要文件
list(APPEND EXAMPLE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/mainwindow.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/icongrid.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/icongrid.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/iconbrowser.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/iconbrowser.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/qtwidgetsample.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/qtwidgetsample.cpp"
)

# 创建可执行文件
qt_add_executable(QIconKitExamples
        ${EXAMPLE_SOURCES}
        MANUAL_FINALIZATION
)

# 简化MOC设置
set_target_properties(QIconKitExamples PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
)
target_compile_definitions(QIconKitExamples
        PRIVATE
        QIconKit_IMPORTS
        QT_SHARED
)

# 包含二进制目录以找到生成的导出头文件
target_include_directories(QIconKitExamples
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_BINARY_DIR}/include
)

# 链接QIconKit库
target_link_libraries(QIconKitExamples
        PRIVATE
        QIconKit::QIconKit
        Qt${QT_VERSION_MAJOR}::Widgets
)

# 设置编译选项
if(MSVC)
    target_compile_options(QIconKitExamples
            PRIVATE
            /W4
            /utf-8
    )
endif()

# 完成Qt设置
qt_finalize_executable(QIconKitExamples)