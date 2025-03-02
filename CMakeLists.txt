cmake_minimum_required(VERSION 3.16)

project(QtIcons
        VERSION 1.0.0
        DESCRIPTION "A Qt Icon library"
        HOMEPAGE_URL "https://github.com/yang1206/qticons"
        LANGUAGES CXX
)

# 设置CMake选项
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
option(QtICON_BUILD_EXAMPLES "Build QtIcons examples" ON)

# 设置CMake变量
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# 设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 查找依赖
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

# 收集源文件 - 修改方式收集所有需要的文件
file(GLOB_RECURSE QtIcons_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

file(GLOB_RECURSE QtIcons_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/QtIcons/*.h"
)

set(QtIcons_RESOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/resources/icons.qrc"
        include/QtIcons/enums/font_awesome.h
)
# # 明确列出带有Q_OBJECT宏的头文件
# set(WRAPPED_HEADER_FILES
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/QtIcons/charts/base/gl_widget.h"
#         "${CMAKE_CURRENT_SOURCE_DIR}/include/QtIcons/utils/orbit_controls.h"
# )

# 为带有Q_OBJECT的类创建专用实现文件
# set(MOC_IMPLEMENTATION_DIR "${CMAKE_CURRENT_BINARY_DIR}/moc_impl")
# file(MAKE_DIRECTORY ${MOC_IMPLEMENTATION_DIR})

# set(MOC_SOURCES)
# foreach(HEADER_PATH ${WRAPPED_HEADER_FILES})
#     get_filename_component(HEADER_NAME ${HEADER_PATH} NAME_WE)
#     set(IMPL_FILE "${MOC_IMPLEMENTATION_DIR}/${HEADER_NAME}_moc_impl.cpp")
#     file(WRITE ${IMPL_FILE} "#include \"${HEADER_PATH}\"\n")
#     list(APPEND MOC_SOURCES ${IMPL_FILE})
# endforeach()

# 添加到源文件列表
# list(APPEND QtIcons_SOURCES ${MOC_SOURCES})

# 创建库目标
if (BUILD_SHARED_LIBS)
    add_library(QtIcons SHARED ${QtIcons_SOURCES} ${QtIcons_HEADERS} ${QtIcons_RESOURCES})
    target_compile_definitions(QtIcons
            PRIVATE
            QtIcons_EXPORTS  # 确保使用与export.h匹配的宏名称
            QtIcons_EXPORTS  # 添加这个以确保兼容性
            PUBLIC
            QtIcons_SHARED
            PUBLIC
            QT_SHARED
    )
    if(MSVC)
        set_target_properties(QtIcons PROPERTIES
                WINDOWS_EXPORT_ALL_SYMBOLS ON
        )
    endif()
else ()
    add_library(QtIcons STATIC ${QtIcons_SOURCES} ${QtIcons_HEADERS}
    )
endif ()

set_target_properties(QtIcons PROPERTIES
        AUTOMOC ON
        AUTORCC ON
        AUTOUIC ON
)


add_library(QtIcons::QtIcons ALIAS QtIcons)

# 生成导出头文件
include(GenerateExportHeader)
generate_export_header(QtIcons
        BASE_NAME QtIcons
        EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/QtIcons/QtIcons_export.h
)

# 设置目标属性
target_include_directories(QtIcons
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}
)

install(
        FILES
        ${CMAKE_CURRENT_BINARY_DIR}/include/QtIcons/QtIcons_export.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/QtIcons
)

# 设置编译选项
target_compile_features(QtIcons PUBLIC cxx_std_20)

# 编译器特定配置
if (MSVC)
    target_compile_options(QtIcons
            PRIVATE
            /W4             # 警告级别
            /Zc:__cplusplus # 启用正确的 __cplusplus 宏
            /utf-8          # 使用 UTF-8 编码
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(QtIcons
            PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -fPIC
    )
endif ()

# 设置调试信息
target_compile_options(QtIcons PRIVATE
        $<$<CONFIG:Debug>:
        $<$<CXX_COMPILER_ID:MSVC>:/Zi>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g>
        >
)

# 链接Qt库
target_link_libraries(QtIcons
        PUBLIC
        Qt${QT_VERSION_MAJOR}::Widgets
)


# 安装配置
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# 安装头文件
install(
        DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/QtIcons
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 安装库文件
install(
        TARGETS QtIcons
        EXPORT QtIconsTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# 导出目标
install(
        EXPORT QtIconsTargets
        FILE QtIconsTargets.cmake
        NAMESPACE QtIcons::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtIcons
)

# 生成版本文件
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/QtIconsConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

# 配置Config文件
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/QtIconsConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/QtIconsConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtIcons
)

# 安装配置文件
install(
        FILES
        "${CMAKE_CURRENT_BINARY_DIR}/QtIconsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/QtIconsConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/QtIcons
)

# 构建示例
if (QtICON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()