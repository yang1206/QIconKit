#include "twotoneicongrid.h"
#include <QHBoxLayout>
#include <QLabel>

TwoToneIconGrid::TwoToneIconGrid(QWidget* parent)
    : IconGrid(parent),
      m_primaryColor(Qt::black),
      m_secondaryColor(QColor(0, 0, 0, 38)) {
    
    // 创建颜色选择控件
    QWidget* colorControlWidget = new QWidget(this);
    QHBoxLayout* colorLayout = new QHBoxLayout(colorControlWidget);

    QLabel* primaryLabel = new QLabel("主要颜色:", colorControlWidget);
    m_primaryColorButton = new QPushButton(colorControlWidget);
    m_primaryColorButton->setFixedSize(24, 24);
    m_primaryColorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(m_primaryColor.name()));
    connect(m_primaryColorButton, &QPushButton::clicked, this, &TwoToneIconGrid::selectPrimaryColor);

    QLabel* secondaryLabel = new QLabel("次要颜色:", colorControlWidget);
    m_secondaryColorButton = new QPushButton(colorControlWidget);
    m_secondaryColorButton->setFixedSize(24, 24);
    m_secondaryColorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(m_secondaryColor.name()));
    connect(m_secondaryColorButton, &QPushButton::clicked, this, &TwoToneIconGrid::selectSecondaryColor);

    colorLayout->addWidget(primaryLabel);
    colorLayout->addWidget(m_primaryColorButton);
    colorLayout->addSpacing(20);
    colorLayout->addWidget(secondaryLabel);
    colorLayout->addWidget(m_secondaryColorButton);
    colorLayout->addStretch();

    // 将颜色控件添加到布局中
    m_mainLayout->insertWidget(0, colorControlWidget);
}

void TwoToneIconGrid::setTwoToneIcons(const QMap<int, QString>& iconMap,
                                     std::function<QIcon(int, int, const QColor&, const QColor&)> iconProvider) {
    // 清除现有图标
    clearIcons();

    // 保存图标提供者
    m_twoToneIconProvider = iconProvider;

    // 添加图标
    int row = 0;
    int col = 0;
    int maxCols = 8; // 每行显示的图标数量

    for (auto it = iconMap.begin(); it != iconMap.end(); ++it) {
        int iconCode = it.key();
        QString iconName = it.value();

        // 创建图标按钮
        IconButton* button = new IconButton(iconCode, iconName, this);
        button->setIcon(m_twoToneIconProvider(iconCode, 32, m_primaryColor, m_secondaryColor));
        button->setToolTip(iconName);

        // 添加到网格
        m_gridLayout->addWidget(button, row, col);
        m_iconButtons[iconName] = button;

        // 连接点击信号
        connect(button, &IconButton::clicked, [this, iconCode, iconName]() {
            emit iconClicked(iconCode, iconName);
        });

        col++;
        if (col >= maxCols) {
            col = 0;
            row++;
        }
    }

    m_countLabel->setText(QString("共 %1 个图标").arg(iconMap.size()));
}

void TwoToneIconGrid::setTwoToneIconProvider(std::function<QIcon(int, int, const QColor&, const QColor&)> iconProvider) {
    m_twoToneIconProvider = iconProvider;
    updateIcons();
}

void TwoToneIconGrid::selectPrimaryColor() {
    QColor color = QColorDialog::getColor(m_primaryColor, this, "选择主要颜色", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        m_primaryColor = color;
        m_primaryColorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(color.name()));
        updateIcons();
    }
}

void TwoToneIconGrid::selectSecondaryColor() {
    QColor color = QColorDialog::getColor(m_secondaryColor, this, "选择次要颜色", QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        m_secondaryColor = color;
        m_secondaryColorButton->setStyleSheet(QString("background-color: %1; border: 1px solid #888;").arg(color.name()));
        updateIcons();
    }
}

void TwoToneIconGrid::updateIcons() {
    // 更新所有图标
    if (m_twoToneIconProvider) {
        for (IconButton* button : m_iconButtons.values()) {
            int iconCode = button->iconCode();
            button->setIcon(m_twoToneIconProvider(iconCode, 32, m_primaryColor, m_secondaryColor));
        }
    }
}