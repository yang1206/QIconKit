#include "iconbrowser.h"
#include <QVBoxLayout>
#include <QMetaEnum>
#include <QtIcons/qticons.h>

IconBrowser::IconBrowser(QWidget* parent) : QWidget(parent) {
    setupUI();
    setupRemixIcons();
    setupLucideIcons();
    setupFontAwesomeIcons();
    setupMaterialIcons();
    // 这里可以添加更多图标类型的设置
}

void IconBrowser::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("图标浏览器", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    m_tabWidget = new QTabWidget(this);
    
    // 创建Remix图标网格
    m_remixIconGrid = new IconGrid();
    m_tabWidget->addTab(m_remixIconGrid, "Remix Icon");

    // 创建Lucide图标网格
    m_lucideIconGrid = new IconGrid();
    m_tabWidget->addTab(m_lucideIconGrid, "Lucide Icon");


    // 创建FontAwesome图标网格
    m_fontAwesomeIconGrid = new IconGrid();
    m_tabWidget->addTab(m_fontAwesomeIconGrid, "FontAwesome");

    m_materialFilledIconGrid = new IconGrid();
    m_materialOutlinedIconGrid = new IconGrid();
    m_materialRoundedIconGrid = new IconGrid();
    m_materialSharpIconGrid = new IconGrid();
    m_materialTwoToneIconGrid = new TwoToneIconGrid();

    // 创建Material图标标签页
    QTabWidget* materialTabWidget = new QTabWidget();
    materialTabWidget->addTab(m_materialFilledIconGrid, "填充");
    materialTabWidget->addTab(m_materialOutlinedIconGrid, "轮廓");
    materialTabWidget->addTab(m_materialRoundedIconGrid, "圆角");
    materialTabWidget->addTab(m_materialSharpIconGrid, "尖角");
    materialTabWidget->addTab(m_materialTwoToneIconGrid, "双色");

    m_tabWidget->addTab(materialTabWidget, "Material Icon");
    
    // 这里可以添加更多图标类型的标签页
    
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_tabWidget);
}

void IconBrowser::setupRemixIcons() {
    // 使用Qt元对象系统获取枚举信息
    QMap<int, QString> iconMap;
    
    const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Remix::Icon>();
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        const char* key = metaEnum.key(i);
        int value = metaEnum.value(i);
        iconMap[value] = QString(key);
    }
    
    // 设置图标提供者函数
    auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
        return QtIcons::QtIcons::remixIcon(static_cast<QtIcons::Remix::Icon>(iconCode), size, color);
    };
    
    // 设置图标
    m_remixIconGrid->setIcons(iconMap, iconProvider);
}


void IconBrowser::setupLucideIcons() {
    // 使用Qt元对象系统获取枚举信息
    QMap<int, QString> iconMap;

    const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Lucide::Icon>();

    if (!metaEnum.isValid()) {
        qWarning() << "无法获取Lucide图标元对象信息!";
        return;
    }
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        const char* key = metaEnum.key(i);
        int value = metaEnum.value(i);
        iconMap[value] = QString(key);
    }

    // 设置图标提供者函数
    auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
        return QtIcons::QtIcons::lucideIcon(static_cast<QtIcons::Lucide::Icon>(iconCode), size, color);
    };

    // 设置图标
    m_lucideIconGrid->setIcons(iconMap, iconProvider);
}

void IconBrowser::setupFontAwesomeIcons() {
    // 使用Qt元对象系统获取枚举信息
    QMap<int, QString> iconMap;

    const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::FontAwesome::Icon>();

    if (!metaEnum.isValid()) {
        qWarning() << "无法获取FontAwesome图标元对象信息!";
        return;
    }
    for (int i = 0; i < metaEnum.keyCount(); ++i) {
        const char* key = metaEnum.key(i);
        int value = metaEnum.value(i);
        iconMap[value] = QString(key);
    }

    // 设置图标提供者函数
    auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
        return QtIcons::QtIcons::fontAwesomeIcon(static_cast<QtIcons::FontAwesome::Icon>(iconCode), size, color);
    };

    // 设置图标
    m_fontAwesomeIconGrid->setIcons(iconMap, iconProvider);
}


void IconBrowser::setupMaterialIcons() {
    // 填充样式
    {
        QMap<int, QString> iconMap;
        const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Material::Filled::Icon>();
        if (metaEnum.isValid()) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                const char* key = metaEnum.key(i);
                int value = metaEnum.value(i);
                iconMap[value] = QString(key);
            }

            auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
                return QtIcons::QtIcons::materialFilledIcon(
                    static_cast<QtIcons::Material::Filled::Icon>(iconCode), size, color);
            };

            m_materialFilledIconGrid->setIcons(iconMap, iconProvider);
        } else {
            qWarning() << "无法获取Material Filled图标元对象信息!";
        }
    }

    // 轮廓样式
    {
        QMap<int, QString> iconMap;
        const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Material::Outlined::Icon>();
        if (metaEnum.isValid()) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                const char* key = metaEnum.key(i);
                int value = metaEnum.value(i);
                iconMap[value] = QString(key);
            }

            auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
                return QtIcons::QtIcons::materialOutlinedIcon(
                    static_cast<QtIcons::Material::Outlined::Icon>(iconCode), size, color);
            };

            m_materialOutlinedIconGrid->setIcons(iconMap, iconProvider);
        } else {
            qWarning() << "无法获取Material Outlined图标元对象信息!";
        }
    }

    // 圆角样式
    {
        QMap<int, QString> iconMap;
        const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Material::Rounded::Icon>();
        if (metaEnum.isValid()) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                const char* key = metaEnum.key(i);
                int value = metaEnum.value(i);
                iconMap[value] = QString(key);
            }

            auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
                return QtIcons::QtIcons::materialRoundedIcon(
                    static_cast<QtIcons::Material::Rounded::Icon>(iconCode), size, color);
            };

            m_materialRoundedIconGrid->setIcons(iconMap, iconProvider);
        } else {
            qWarning() << "无法获取Material Rounded图标元对象信息!";
        }
    }

    // 尖角样式
    {
        QMap<int, QString> iconMap;
        const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Material::Sharp::Icon>();
        if (metaEnum.isValid()) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                const char* key = metaEnum.key(i);
                int value = metaEnum.value(i);
                iconMap[value] = QString(key);
            }

            auto iconProvider = [](int iconCode, int size, const QColor& color) -> QIcon {
                return QtIcons::QtIcons::materialSharpIcon(
                    static_cast<QtIcons::Material::Sharp::Icon>(iconCode), size, color);
            };

            m_materialSharpIconGrid->setIcons(iconMap, iconProvider);
        } else {
            qWarning() << "无法获取Material Sharp图标元对象信息!";
        }
    }

    // 双色样式
    {
        QMap<int, QString> iconMap;
        const QMetaEnum metaEnum = QMetaEnum::fromType<QtIcons::Material::TwoTone::Icon>();
        if (metaEnum.isValid()) {
            for (int i = 0; i < metaEnum.keyCount(); ++i) {
                const char* key = metaEnum.key(i);
                int value = metaEnum.value(i);
                iconMap[value] = QString(key);
            }

            auto iconProvider = [](int iconCode, int size, const QColor& primaryColor, const QColor& secondaryColor) -> QIcon {
                return QtIcons::QtIcons::materialTwoToneIcon(
                    static_cast<QtIcons::Material::TwoTone::Icon>(iconCode),
                    size,
                    primaryColor,
                    secondaryColor);
            };

            m_materialTwoToneIconGrid->setTwoToneIcons(iconMap, iconProvider);
        } else {
            qWarning() << "无法获取Material TwoTone图标元对象信息!";
        }
    }
}