#include "icongrid.h"
#include <QApplication>
#include <QClipboard>
#include <QIconKit/qiconkit.h>
#include <QMetaEnum>
#include <QTimer>
#include <QToolTip>
#include <QVBoxLayout>

IconButton::IconButton(int iconCode, const QString& name, QWidget* parent)
    : QPushButton(parent), m_iconName(name), m_iconCode(iconCode) {
    setToolTip(QString("%1 (0x%2)").arg(name).arg(iconCode, 0, 16));
    setFixedSize(64, 64);

    // 设置样式
    setStyleSheet("QPushButton {"
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
                  "}");

    connect(this, &QPushButton::clicked, this, &IconButton::copyIconName);
}

void IconButton::copyIconName() {
    QClipboard* clipboard = QApplication::clipboard();
    clipboard->setText(m_iconName);

    // 显示提示
    QToolTip::showText(QCursor::pos(), QString("已复制: %1").arg(m_iconName), this);

    // 2秒后隐藏提示
    QTimer::singleShot(2000, []() { QToolTip::hideText(); });
}

IconGrid::IconGrid(QWidget* parent) : QWidget(parent) { setupUI(); }

void IconGrid::setupUI() {
    m_mainLayout = new QVBoxLayout(this);

    // 搜索框
    m_searchBox = new QLineEdit(this);
    m_searchBox->setPlaceholderText("搜索图标...");
    m_searchBox->setClearButtonEnabled(true);
    connect(m_searchBox, &QLineEdit::textChanged, this, &IconGrid::filterIcons);

    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    m_searchTimer->setInterval(300); // 300ms 延迟

    connect(m_searchBox, &QLineEdit::textChanged, this, [this](const QString& text) {
        m_searchTimer->stop();
        m_searchTimer->start();
    });
    connect(m_searchTimer, &QTimer::timeout, this, [this]() { filterIcons(m_searchBox->text()); });

    // 计数标签
    m_countLabel = new QLabel(this);

    // 滚动区域
    m_scrollArea    = new QScrollArea(this);
    m_scrollContent = new QWidget(m_scrollArea);
    m_gridLayout    = new QGridLayout(m_scrollContent);
    m_gridLayout->setSpacing(8);

    m_scrollArea->setWidget(m_scrollContent);
    m_scrollArea->setWidgetResizable(true);

    // 分页控件
    m_paginationLayout = new QHBoxLayout;
    m_prevButton       = new QPushButton("上一页", this);
    m_nextButton       = new QPushButton("下一页", this);
    m_pageLabel        = new QLabel(this);

    m_paginationLayout->addStretch();
    m_paginationLayout->addWidget(m_prevButton);
    m_paginationLayout->addWidget(m_pageLabel);
    m_paginationLayout->addWidget(m_nextButton);
    m_paginationLayout->addStretch();

    connect(m_prevButton, &QPushButton::clicked, this, [this]() {
        if (m_currentPage > 0) {
            onPageChanged(m_currentPage - 1);
        }
    });
    connect(m_nextButton, &QPushButton::clicked, this, [this]() {
        if (m_currentPage < m_totalPages - 1) {
            onPageChanged(m_currentPage + 1);
        }
    });

    // 添加到主布局
    m_mainLayout->addWidget(m_searchBox);
    m_mainLayout->addWidget(m_countLabel);
    m_mainLayout->addWidget(m_scrollArea);
    m_mainLayout->addLayout(m_paginationLayout);
}

void IconGrid::clearIcons() {
    clearCurrentPageButtons();
    m_filteredIcons.clear();
    m_originalIcons.clear();
}

void IconGrid::clearCurrentPageButtons() {
    // 清除并删除当前页的所有按钮
    for (auto button : m_currentPageButtons.values()) {
        m_gridLayout->removeWidget(button);
        delete button;
    }
    m_currentPageButtons.clear();
}

void IconGrid::setIcons(const QMap<int, QString>&                            iconMap,
                        const std::function<QIcon(int, int, const QColor&)>& iconProvider) {
    clearIcons();
    m_iconProvider = iconProvider;

    // 存储原始图标数据
    m_originalIcons.reserve(iconMap.size());
    for (auto it = iconMap.begin(); it != iconMap.end(); ++it) {
        m_originalIcons.append({it.key(), it.value()});
    }

    // 初始显示所有图标
    filterIcons("");
}

void IconGrid::filterIcons(const QString& filter) {
    clearCurrentPageButtons();

    // 从原始数据中过滤
    m_filteredIcons.clear();
    m_filteredIcons.reserve(m_originalIcons.size());

    for (const auto& iconData : m_originalIcons) {
        if (filter.isEmpty() || iconData.second.contains(filter, Qt::CaseInsensitive)) {
            m_filteredIcons.append(iconData);
        }
    }

    // 计算总页数
    m_totalPages  = (m_filteredIcons.size() + ICONS_PER_PAGE - 1) / ICONS_PER_PAGE;
    m_currentPage = 0;

    // 更新分页控件状态
    m_prevButton->setEnabled(false);
    m_nextButton->setEnabled(m_totalPages > 1);

    // 显示当前页
    onPageChanged(0);

    m_countLabel->setText(QString("共 %1 个图标").arg(m_filteredIcons.size()));
}

void IconGrid::onPageChanged(int page) {
    clearCurrentPageButtons();

    m_currentPage = page;

    // 计算当前页的图标范围
    int startIndex = page * ICONS_PER_PAGE;
    int endIndex   = qMin(startIndex + ICONS_PER_PAGE, m_filteredIcons.size());

    // 创建并显示当前页的图标
    int maxCols    = 8;
    int currentRow = 0;
    int currentCol = 0;

    // 重置布局
    QLayoutItem* item;
    while ((item = m_gridLayout->takeAt(0)) != nullptr) {
        delete item;
    }

    for (int i = startIndex; i < endIndex; ++i) {
        const auto& iconData = m_filteredIcons[i];
        IconButton* button   = new IconButton(iconData.first, iconData.second, m_scrollContent);
        button->setIcon(m_iconProvider(iconData.first, 32, Qt::black));

        m_gridLayout->addWidget(button, currentRow, currentCol);
        m_currentPageButtons[i - startIndex] = button;

        // 更新行列位置
        currentCol++;
        if (currentCol >= maxCols) {
            currentCol = 0;
            currentRow++;
        }
    }

    // 更新分页控件
    m_prevButton->setEnabled(page > 0);
    m_nextButton->setEnabled(page < m_totalPages - 1);
    m_pageLabel->setText(QString("第 %1/%2 页").arg(page + 1).arg(m_totalPages));
}