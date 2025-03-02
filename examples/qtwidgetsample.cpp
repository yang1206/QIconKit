#include "qtwidgetsample.h"
#include <QtIcons/qticons.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QTabBar>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QTreeWidget>
#include <QListWidget>
#include <QTableWidget>

QtWidgetSample::QtWidgetSample(QWidget *parent) : QWidget(parent) {
    setupUI();
    addWidgetSamples();
}

void QtWidgetSample::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    QLabel* titleLabel = new QLabel("Qt控件图标示例", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(16);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setWidgetResizable(true);
    m_contentWidget = new QWidget(m_scrollArea);
    m_scrollArea->setWidget(m_contentWidget);
    
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_scrollArea);
}

void QtWidgetSample::addWidgetSamples() {
    QVBoxLayout* contentLayout = new QVBoxLayout(m_contentWidget);
    
    // 按钮示例
    QGroupBox* buttonGroup = new QGroupBox("按钮控件", m_contentWidget);
    QVBoxLayout* buttonLayout = new QVBoxLayout(buttonGroup);
    
    // QPushButton示例
    QHBoxLayout* pushButtonLayout = new QHBoxLayout();
    QLabel* pushButtonLabel = new QLabel("QPushButton:");
    pushButtonLabel->setMinimumWidth(120);
    
    QPushButton* btn1 = new QPushButton("账户");
    btn1->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::AccountCircleFill, 16));
    
    QPushButton* btn2 = new QPushButton("设置");
    btn2->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::Settings4Fill, 16));
    
    QPushButton* btn3 = new QPushButton("警告");
    btn3->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::AlarmWarningFill, 16, Qt::red));
    
    pushButtonLayout->addWidget(pushButtonLabel);
    pushButtonLayout->addWidget(btn1);
    pushButtonLayout->addWidget(btn2);
    pushButtonLayout->addWidget(btn3);
    pushButtonLayout->addStretch();
    
    // QToolButton示例
    QHBoxLayout* toolButtonLayout = new QHBoxLayout();
    QLabel* toolButtonLabel = new QLabel("QToolButton:");
    toolButtonLabel->setMinimumWidth(120);
    
    QToolButton* toolBtn1 = new QToolButton();
    toolBtn1->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FileAddFill, 16));
    toolBtn1->setToolTip("添加文件");
    
    QToolButton* toolBtn2 = new QToolButton();
    toolBtn2->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::DeleteBin2Fill, 16));
    toolBtn2->setToolTip("删除");
    
    QToolButton* toolBtn3 = new QToolButton();
    toolBtn3->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::SaveFill, 16));
    toolBtn3->setToolTip("保存");
    
    toolButtonLayout->addWidget(toolButtonLabel);
    toolButtonLayout->addWidget(toolBtn1);
    toolButtonLayout->addWidget(toolBtn2);
    toolButtonLayout->addWidget(toolBtn3);
    toolButtonLayout->addStretch();
    
    // QRadioButton示例
    QHBoxLayout* radioButtonLayout = new QHBoxLayout();
    QLabel* radioButtonLabel = new QLabel("QRadioButton:");
    radioButtonLabel->setMinimumWidth(120);
    
    QRadioButton* radioBtn1 = new QRadioButton("选项1");
    radioBtn1->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::CheckboxCircleFill, 16));
    
    QRadioButton* radioBtn2 = new QRadioButton("选项2");
    radioBtn2->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::CheckboxCircleLine, 16));
    
    radioButtonLayout->addWidget(radioButtonLabel);
    radioButtonLayout->addWidget(radioBtn1);
    radioButtonLayout->addWidget(radioBtn2);
    radioButtonLayout->addStretch();
    
    // QCheckBox示例
    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    QLabel* checkBoxLabel = new QLabel("QCheckBox:");
    checkBoxLabel->setMinimumWidth(120);
    
    QCheckBox* checkBox1 = new QCheckBox("选项A");
    checkBox1->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::CheckboxFill, 16));
    
    QCheckBox* checkBox2 = new QCheckBox("选项B");
    checkBox2->setIcon(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::CheckboxLine, 16));
    
    checkBoxLayout->addWidget(checkBoxLabel);
    checkBoxLayout->addWidget(checkBox1);
    checkBoxLayout->addWidget(checkBox2);
    checkBoxLayout->addStretch();
    
    buttonLayout->addLayout(pushButtonLayout);
    buttonLayout->addLayout(toolButtonLayout);
    buttonLayout->addLayout(radioButtonLayout);
    buttonLayout->addLayout(checkBoxLayout);
    
    // 下拉菜单示例
    QGroupBox* comboGroup = new QGroupBox("下拉菜单", m_contentWidget);
    QVBoxLayout* comboLayout = new QVBoxLayout(comboGroup);
    
    QHBoxLayout* comboBoxLayout = new QHBoxLayout();
    QLabel* comboBoxLabel = new QLabel("QComboBox:");
    comboBoxLabel->setMinimumWidth(120);
    
    QComboBox* comboBox = new QComboBox();
    comboBox->addItem(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::UserFill, 16), "用户");
    comboBox->addItem(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::GroupFill, 16), "群组");
    comboBox->addItem(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::AdminFill, 16), "管理员");
    
    comboBoxLayout->addWidget(comboBoxLabel);
    comboBoxLayout->addWidget(comboBox);
    comboBoxLayout->addStretch();
    
    comboLayout->addLayout(comboBoxLayout);
    
    // 标签页示例
    QGroupBox* tabGroup = new QGroupBox("标签页", m_contentWidget);
    QVBoxLayout* tabLayout = new QVBoxLayout(tabGroup);
    
    QTabBar* tabBar = new QTabBar();
    tabBar->addTab(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::Home4Fill, 16), "首页");
    tabBar->addTab(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::Settings3Fill, 16), "设置");
    tabBar->addTab(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::UserFill, 16), "用户");
    
    tabLayout->addWidget(tabBar);
    
    // 工具栏示例
    QGroupBox* toolbarGroup = new QGroupBox("工具栏", m_contentWidget);
    QVBoxLayout* toolbarLayout = new QVBoxLayout(toolbarGroup);
    
    QToolBar* toolbar = new QToolBar();
    toolbar->addAction(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FileAddFill, 16), "新建");
    toolbar->addAction(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FolderOpenFill, 16), "打开");
    toolbar->addAction(QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::SaveFill, 16), "保存");
    toolbar->addSeparator();
    toolbar->addAction(QtIcons::QtIcons::lucideIcon(QtIcons::Lucide::Icon::ClipboardCheck, 16), "剪切");
    toolbar->addAction(QtIcons::QtIcons::lucideIcon(QtIcons::Lucide::Icon::ClipboardCopy, 16), "复制");
    toolbar->addAction(QtIcons::QtIcons::lucideIcon(QtIcons::Lucide::Icon::ClipboardPaste, 16), "粘贴");
    
    toolbarLayout->addWidget(toolbar);
    
    // 树形控件示例
    QGroupBox* treeGroup = new QGroupBox("树形控件", m_contentWidget);
    QVBoxLayout* treeLayout = new QVBoxLayout(treeGroup);
    
    QTreeWidget* treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabel("文件结构");
    treeWidget->setMaximumHeight(150);
    
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, "项目");
    rootItem->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* srcItem = new QTreeWidgetItem(rootItem);
    srcItem->setText(0, "源代码");
    srcItem->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* fileItem1 = new QTreeWidgetItem(srcItem);
    fileItem1->setText(0, "main.cpp");
    fileItem1->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FileFill, 16));
    
    QTreeWidgetItem* fileItem2 = new QTreeWidgetItem(srcItem);
    fileItem2->setText(0, "widget.cpp");
    fileItem2->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FileFill, 16));
    
    QTreeWidgetItem* resItem = new QTreeWidgetItem(rootItem);
    resItem->setText(0, "资源");
    resItem->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* imgItem = new QTreeWidgetItem(resItem);
    imgItem->setText(0, "logo.png");
    imgItem->setIcon(0, QtIcons::QtIcons::remixIcon(QtIcons::Remix::Icon::ImageFill, 16));
    
    treeWidget->expandAll();
    treeLayout->addWidget(treeWidget);
    
    // 添加所有组到主布局
    contentLayout->addWidget(buttonGroup);
    contentLayout->addWidget(comboGroup);
    contentLayout->addWidget(tabGroup);
    contentLayout->addWidget(toolbarGroup);
    contentLayout->addWidget(treeGroup);
    contentLayout->addStretch();
} 