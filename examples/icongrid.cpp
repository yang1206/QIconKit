#include "icongrid.h"
#include <QIconKit/qiconkit.h>
#include <QVBoxLayout>
#include <QToolTip>
#include <QTimer>
#include <QClipboard>
#include <QApplication>
#include <QMetaEnum>

IconButton::IconButton(int iconCode, const QString& name, QWidget* parent)
    : QPushButton(parent), m_iconName(name), m_iconCode(iconCode)
{
    setToolTip(QString("%1 (0x%2)").arg(name).arg(iconCode, 0, 16));
    setFixedSize(64, 64);

    // 设置样式
    setStyleSheet(
        "QPushButton {"
        "   border: 1px solid #ddd;"
        "   border-radius: 4px;"
        "   padding: 4px;"
        "   background-color: #f8f8f8;"
        "}"
        "QPushButton:hover {"
        "   background-color: #e8e8e8;"
        "   border: 1px solid #ccc;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #d8d8d8;"
        "}"
    );

    connect(this, &QPushButton::clicked, this, &IconButton::copyIconName);
}

void IconButton::copyIconName()
{
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(m_iconName);
    
    // 显示提示
    QToolTip::showText(QCursor::pos(), QString("已复制: %1").arg(m_iconName), this);
    
    // 2秒后隐藏提示
    QTimer::singleShot(2000, []() {
        QToolTip::hideText();
    });
}

IconGrid::IconGrid(QWidget* parent)
    : QWidget(parent)
{
    setupUI();
}

void IconGrid::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    
    // 搜索框
    m_searchBox = new QLineEdit(this);
    m_searchBox->setPlaceholderText("搜索图标...");
    m_searchBox->setClearButtonEnabled(true);
    connect(m_searchBox, &QLineEdit::textChanged, this, &IconGrid::filterIcons);
    
    // 计数标签
    m_countLabel = new QLabel(this);
    
    // 滚动区域
    m_scrollArea = new QScrollArea(this);
    m_scrollContent = new QWidget(m_scrollArea);
    m_gridLayout = new QGridLayout(m_scrollContent);
    m_gridLayout->setSpacing(8);
    
    m_scrollArea->setWidget(m_scrollContent);
    m_scrollArea->setWidgetResizable(true);
    
    // 添加到主布局
    m_mainLayout->addWidget(m_searchBox);
    m_mainLayout->addWidget(m_countLabel);
    m_mainLayout->addWidget(m_scrollArea);
}

void IconGrid::clearIcons()
{
    // 清除现有图标
    for (auto button : m_iconButtons.values()) {
        m_gridLayout->removeWidget(button);
        delete button;
    }
    m_iconButtons.clear();
}

void IconGrid::setIcons(const QMap<int, QString>& iconMap, const std::function<QIcon(int, int, const QColor&)>& iconProvider)
{
    // 清除现有图标
    for (auto button : m_iconButtons.values()) {
        m_gridLayout->removeWidget(button);
        delete button;
    }
    m_iconButtons.clear();
    
    // 保存图标提供者函数
    m_iconProvider = iconProvider;
    
    // 创建图标网格
    int row = 0;
    int col = 0;
    int maxCols = 8; // 每行显示的图标数量
    
    for (auto it = iconMap.begin(); it != iconMap.end(); ++it) {
        int iconCode = it.key();
        QString name = it.value();
        
        IconButton* button = new IconButton(iconCode, name, this);
        button->setIcon(m_iconProvider(iconCode, 32, Qt::black));
        m_gridLayout->addWidget(button, row, col);
        m_iconButtons[name] = button;
        
        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }
    
    m_countLabel->setText(QString("共 %1 个图标").arg(iconMap.size()));
}

void IconGrid::filterIcons(const QString& filter)
{
    int visibleCount = 0;
    
    if (filter.isEmpty()) {
        // 显示所有图标
        for (auto button : m_iconButtons.values()) {
            button->show();
            visibleCount++;
        }
    } else {
        // 只显示匹配的图标
        for (auto it = m_iconButtons.begin(); it != m_iconButtons.end(); ++it) {
            bool match = it.key().contains(filter, Qt::CaseInsensitive);
            it.value()->setVisible(match);
            if (match) visibleCount++;
        }
    }
    
    m_countLabel->setText(QString("显示 %1/%2 个图标").arg(visibleCount).arg(m_iconButtons.size()));
} 