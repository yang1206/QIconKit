# QtIcons

[![License: LGPL v3](https://img.shields.io/badge/License-LGPL%20v3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)
![C++](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![Qt](https://img.shields.io/badge/Qt-5%2F6-green.svg)

QtIcons 是一个简单易用的 Qt 图标库，为您的 Qt 应用程序提供丰富的图标集合。该库支持多种流行的图标集，包括 Material Design、Remix、Lucide 和 Font Awesome 等，让您可以轻松地为应用添加现代化的图标。

## 特性

- 🎨 **多种图标集合**：Material Design、Remix Icon、Lucide 和 Font Awesome
- 🌈 **多种样式变体**：Material Icons 支持 Filled、Outlined、Rounded、Sharp 和 TwoTone 等变体
- 🔄 **动态颜色**：可以轻松更改图标颜色
- 💡 **双色支持**：支持 Material Design 的双色图标效果
- 🔍 **高 DPI 支持**：图标在高分辨率显示器上也能保持清晰
- 🧩 **简单集成**：易于集成到 Qt 项目中，支持 CMake

## 支持的图标集

### Material Icons
- **Filled**: 默认填充样式 (~2000 图标)
- **Outlined**: 轮廓线样式
- **Rounded**: 圆角样式
- **Sharp**: 尖角样式
- **TwoTone**: 双色样式

### Remix Icons
现代风格的图标集，提供了丰富的图标选择 

### Lucide Icons
简洁明了的线条图标 

### Font Awesome Icons
世界上最受欢迎的图标集之一

## 系统要求

- C++17 兼容的编译器
- Qt 5.15+ 或 Qt 6.x
- CMake 3.16+

## 安装

### 方法 1：使用 CMake FetchContent（推荐）

在你的 CMakeLists.txt 中添加：
```cmake
include(FetchContent)
FetchContent_Declare(
    QtIcons
    GIT_REPOSITORY https://github.com/yang1206/qticons.git
    GIT_TAG main
)
FetchContent_MakeAvailable(QtIcons)

target_link_libraries(YourTarget PRIVATE QtIcons::QtIcons)
```

### 方法 2：手动构建和安装

```bash
# Clone 仓库
git clone https://github.com/yang1206/qticons.git
cd qticons

# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 编译
cmake --build . --config Release

# 安装（可选）
cmake --install .
```

然后在你的 CMakeLists.txt 中添加：

```cmake
find_package(QtIcons REQUIRED)
target_link_libraries(your_target PRIVATE QtIcons::QtIcons)
```

## 使用方法

### 初始化

在使用任何图标之前，需要先初始化库：

```cpp
#include <QtIcons/qticons.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // 初始化图标库
    QtIcons::QtIcons::initialize();
    
    // 现在可以使用图标了
    // ...
    
    return app.exec();
}
```

### 基本用法

```cpp
#include <QtIcons/qticons.h>
#include <QPushButton>

// 创建一个带有 Material Design 图标的按钮
QPushButton button;
button.setIcon(QtIcons::QtIcons::materialFilledIcon(QtIcons::Material::Filled::Home));
button.show();
```

### 设置图标颜色

```cpp
// 设置自定义颜色
button.setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Home, 24, QColor(0, 120, 215)));
```

### 使用双色图标 (Material Design)

```cpp
// 设置双色图标，带有主要颜色和次要颜色
QIcon twoToneIcon = QtIcons::QtIcons::materialTwoToneIcon(
    QtIcons::Material::TwoTone::Favorite,  // 图标
    32,                                    // 大小
    QColor(0, 120, 215),                  // 主要颜色
    QColor(0, 0, 0, 38)                   // 次要颜色 (带透明度)
);
button.setIcon(twoToneIcon);
```

### 各图标类型示例

```cpp
// Material Design 图标
button1.setIcon(QtIcons::QtIcons::materialFilledIcon(QtIcons::Material::Filled::Home));
button2.setIcon(QtIcons::QtIcons::materialOutlinedIcon(QtIcons::Material::Outlined::Home));
button3.setIcon(QtIcons::QtIcons::materialRoundedIcon(QtIcons::Material::Rounded::Home));
button4.setIcon(QtIcons::QtIcons::materialSharpIcon(QtIcons::Material::Sharp::Home));
button5.setIcon(QtIcons::QtIcons::materialTwoToneIcon(QtIcons::Material::TwoTone::Home));

// Remix 图标
button6.setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Home));

// Lucide 图标
button7.setIcon(QtIcons::QtIcons::lucideIcon(QtIcons::Lucide::Home));

// Font Awesome 图标
button8.setIcon(QtIcons::QtIcons::fontAwesomeIcon(QtIcons::FontAwesome::Home));
```

## 图标浏览器

QtIcons 包含一个图标浏览器示例，您可以通过以下命令运行：

```bash
./bin/QtIconsExamples
```

图标浏览器提供了一个直观的界面，让您可以浏览所有可用的图标，并支持搜索和颜色自定义功能。

## 构建选项

- `BUILD_SHARED_LIBS`: 构建动态库 (默认: ON)
- `QtICON_BUILD_EXAMPLES`: 构建示例程序 (默认: ON)

## 自定义图标工厂

如果您需要创建自己的图标工厂，可以继承 `FontIconProvider` 类：

```cpp
class MyIconFactory : public QtIcons::FontIconProvider {
public:
    static MyIconFactory& instance() {
        static MyIconFactory s_instance;
        return s_instance;
    }
    
    QIcon myIcon(int iconCode, int size, const QColor& color) const {
        return iconFromCode(iconCode, size, color);
    }
    
private:
    MyIconFactory() 
        : FontIconProvider("My Icon Font", ":/fonts/my_icon_font.ttf") {
    }
};
```

## 注意事项

1. 图标大小
   - Material Icons 默认大小为 24px
   - 其他图标默认大小为 16px
   - 可以通过参数自定义大小

2. 双色图标
   - 目前仅 Material TwoTone 图标支持双色效果
   - 默认次要颜色为半透明黑色 (0, 0, 0, 38)

3. 高 DPI 支持
   - 图标会根据设备像素比例自动缩放
   - 建议使用矢量图标以获得最佳效果

## 许可证

此项目采用 LGPL V3 许可证 - 详情请参阅 [LICENSE](LICENSE) 文件。

## 致谢

- [Material Design Icons](https://fonts.google.com/icons)
- [Remix Icons](https://remixicon.com/)
- [Lucide Icons](https://lucide.dev/)
- [Font Awesome](https://fontawesome.com/)

## 贡献

欢迎贡献！如果您想为 QtIcons 添加新功能、修复问题或改进文档，请提交 Pull Request。
