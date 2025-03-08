#include "qtwidgetsample.h"
#include <QIconKit/qiconkit.h>
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
    addAnimationSamples();
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
    btn1->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::AccountCircleFill, 30));
    btn1->setIconSize(QSize(30, 30));
    btn1->setFixedSize(100, 60);
    
    QPushButton* btn2 = new QPushButton("设置");
    btn2->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::Settings4Fill, 16));
    
    QPushButton* btn3 = new QPushButton("警告");
    btn3->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::AlarmWarningFill, 16, Qt::red));
    
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
    toolBtn1->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FileAddFill, 16));
    toolBtn1->setToolTip("添加文件");
    
    QToolButton* toolBtn2 = new QToolButton();
    toolBtn2->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::DeleteBin2Fill, 16));
    toolBtn2->setToolTip("删除");
    
    QToolButton* toolBtn3 = new QToolButton();
    toolBtn3->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::SaveFill, 16));
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
    radioBtn1->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::CheckboxCircleFill, 16));
    
    QRadioButton* radioBtn2 = new QRadioButton("选项2");
    radioBtn2->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::CheckboxCircleLine, 16));
    
    radioButtonLayout->addWidget(radioButtonLabel);
    radioButtonLayout->addWidget(radioBtn1);
    radioButtonLayout->addWidget(radioBtn2);
    radioButtonLayout->addStretch();
    
    // QCheckBox示例
    QHBoxLayout* checkBoxLayout = new QHBoxLayout();
    QLabel* checkBoxLabel = new QLabel("QCheckBox:");
    checkBoxLabel->setMinimumWidth(120);
    
    QCheckBox* checkBox1 = new QCheckBox("选项A");
    checkBox1->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::CheckboxFill, 16));
    
    QCheckBox* checkBox2 = new QCheckBox("选项B");
    checkBox2->setIcon(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::CheckboxLine, 16));
    
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
    comboBox->addItem(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::UserFill, 16), "用户");
    comboBox->addItem(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::GroupFill, 16), "群组");
    comboBox->addItem(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::AdminFill, 16), "管理员");
    
    comboBoxLayout->addWidget(comboBoxLabel);
    comboBoxLayout->addWidget(comboBox);
    comboBoxLayout->addStretch();
    
    comboLayout->addLayout(comboBoxLayout);
    
    // 标签页示例
    QGroupBox* tabGroup = new QGroupBox("标签页", m_contentWidget);
    QVBoxLayout* tabLayout = new QVBoxLayout(tabGroup);
    
    QTabBar* tabBar = new QTabBar();
    tabBar->addTab(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::Home4Fill, 16), "首页");
    tabBar->addTab(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::Settings3Fill, 16), "设置");
    tabBar->addTab(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::UserFill, 16), "用户");
    
    tabLayout->addWidget(tabBar);
    
    // 工具栏示例
    QGroupBox* toolbarGroup = new QGroupBox("工具栏", m_contentWidget);
    QVBoxLayout* toolbarLayout = new QVBoxLayout(toolbarGroup);
    
    QToolBar* toolbar = new QToolBar();
    toolbar->addAction(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FileAddFill, 16), "新建");
    toolbar->addAction(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FolderOpenFill, 16), "打开");
    toolbar->addAction(QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::SaveFill, 16), "保存");
    toolbar->addSeparator();
    toolbar->addAction(QIconKit::QIconKit::lucideIcon(QIconKit::Lucide::Icon::ClipboardCheck, 16), "剪切");
    toolbar->addAction(QIconKit::QIconKit::lucideIcon(QIconKit::Lucide::Icon::ClipboardCopy, 16), "复制");
    toolbar->addAction(QIconKit::QIconKit::lucideIcon(QIconKit::Lucide::Icon::ClipboardPaste, 16), "粘贴");
    
    toolbarLayout->addWidget(toolbar);
    
    // 树形控件示例
    QGroupBox* treeGroup = new QGroupBox("树形控件", m_contentWidget);
    QVBoxLayout* treeLayout = new QVBoxLayout(treeGroup);
    
    QTreeWidget* treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabel("文件结构");
    treeWidget->setMaximumHeight(150);
    
    QTreeWidgetItem* rootItem = new QTreeWidgetItem(treeWidget);
    rootItem->setText(0, "项目");
    rootItem->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* srcItem = new QTreeWidgetItem(rootItem);
    srcItem->setText(0, "源代码");
    srcItem->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* fileItem1 = new QTreeWidgetItem(srcItem);
    fileItem1->setText(0, "main.cpp");
    fileItem1->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FileFill, 16));
    
    QTreeWidgetItem* fileItem2 = new QTreeWidgetItem(srcItem);
    fileItem2->setText(0, "widget.cpp");
    fileItem2->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FileFill, 16));
    
    QTreeWidgetItem* resItem = new QTreeWidgetItem(rootItem);
    resItem->setText(0, "资源");
    resItem->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::FolderFill, 16));
    
    QTreeWidgetItem* imgItem = new QTreeWidgetItem(resItem);
    imgItem->setText(0, "logo.png");
    imgItem->setIcon(0, QIconKit::QIconKit::remixIcon(QIconKit::Remix::Icon::ImageFill, 16));
    
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

void QtWidgetSample::addAnimationSamples() {
    QVBoxLayout* contentLayout = qobject_cast<QVBoxLayout*>(m_contentWidget->layout());
    if (!contentLayout) return;
    
    // 创建动画图标组
    QGroupBox* animGroup = new QGroupBox("动画图标示例", m_contentWidget);
    QVBoxLayout* animMainLayout = new QVBoxLayout(animGroup);
    
    // 添加动画控制按钮
    QHBoxLayout* controlLayout = new QHBoxLayout();
    QPushButton* startBtn = new QPushButton("全部开始");
    QPushButton* stopBtn = new QPushButton("全部停止");
    QPushButton* pauseBtn = new QPushButton("全部暂停");
    QPushButton* resumeBtn = new QPushButton("全部恢复");
    
    connect(startBtn, &QPushButton::clicked, this, &QtWidgetSample::startAllAnimations);
    connect(stopBtn, &QPushButton::clicked, this, &QtWidgetSample::stopAllAnimations);
    connect(pauseBtn, &QPushButton::clicked, this, &QtWidgetSample::pauseAllAnimations);
    connect(resumeBtn, &QPushButton::clicked, this, &QtWidgetSample::resumeAllAnimations);
    
    controlLayout->addWidget(startBtn);
    controlLayout->addWidget(stopBtn);
    controlLayout->addWidget(pauseBtn);
    controlLayout->addWidget(resumeBtn);
    animMainLayout->addLayout(controlLayout);
    
    // 网格布局放置动画示例
    QGridLayout* animGrid = new QGridLayout();
    
    // 定义所有示例
    struct AnimExample {
        QString name;
        QIconKit::Remix::Icon icon;
        QIconKit::AnimationType type;
        int size;
        QColor color;
        QIconKit::AnimationParams params;
    };
    
    // 创建各种动画类型的示例
    QList<AnimExample> examples = {
        {"旋转 (Spin)", QIconKit::Remix::Icon::Loader4Line, QIconKit::AnimationType::Spin, 32, Qt::blue},
        {"脉冲 (Pulse)", QIconKit::Remix::Icon::HeartFill, QIconKit::AnimationType::Pulse, 32, Qt::red},
        {"弹跳 (Bounce)", QIconKit::Remix::Icon::ArrowUpLine, QIconKit::AnimationType::Bounce, 32, Qt::darkGreen},
        {"摇晃 (Shake)", QIconKit::Remix::Icon::AlarmFill, QIconKit::AnimationType::Shake, 32, Qt::darkRed},
        {"淡入淡出 (Fade)", QIconKit::Remix::Icon::GhostFill, QIconKit::AnimationType::Fade, 32, Qt::darkGray},
        {"闪烁 (Blink)", QIconKit::Remix::Icon::AlertFill, QIconKit::AnimationType::Blink, 32, Qt::darkYellow},
        {"心跳 (Beat)", QIconKit::Remix::Icon::HeartPulseLine, QIconKit::AnimationType::Beat, 32, Qt::magenta},
        {"翻转 (Flip)", QIconKit::Remix::Icon::RefreshLine, QIconKit::AnimationType::Flip, 32, Qt::darkCyan}
    };
    
    // 自定义参数
    // Pulse参数
    examples[1].params.minScale = 0.7;
    examples[1].params.maxScale = 1.3;
    examples[1].params.duration = 1500;
    
    // Blink参数
    examples[5].params.duration = 2000; 
    
    // Beat参数
    examples[6].params.maxScale = 1.5;
    examples[6].params.duration = 800;
    
    // 创建所有动画示例
    int row = 0, col = 0;
    const int maxCol = 4; // 每行最多4个示例
    
    for (const auto& example : examples) {
        QVBoxLayout* itemLayout = new QVBoxLayout();
        
        // 标签
        QLabel* label = new QLabel(example.name);
        label->setAlignment(Qt::AlignCenter);


        
        QIconKit::AnimatedIcon* animatedIcon = QIconKit::QIconKit::createAnimatedRemixIcon(
        example.icon, example.type, example.size, example.color, example.params);
        
        // 添加到列表以便后续控制
        m_animatedIcons.append(animatedIcon);
        
        itemLayout->addWidget(label);
        itemLayout->addWidget(animatedIcon, 0, Qt::AlignCenter);
        
        animGrid->addLayout(itemLayout, row, col);
        
        col++;
        if (col >= maxCol) {
            col = 0;
            row++;
        }
    }
    
    // 使用不同的图标库也创建几个动画示例
    QVBoxLayout* materialLayout = new QVBoxLayout();
    QLabel* materialLabel = new QLabel("Material动画");
    materialLabel->setAlignment(Qt::AlignCenter);
    
    QIconKit::AnimationParams materialParams;
    materialParams.duration = 2000;
    QIconKit::AnimatedIcon* materialIcon = AnimatedMaterialFilledIcon(
        Settings, QIconKit::AnimationType::Spin, 32, Qt::darkBlue, materialParams);
    m_animatedIcons.append(materialIcon);
    
    materialLayout->addWidget(materialLabel);
    materialLayout->addWidget(materialIcon, 0, Qt::AlignCenter);
    
    QVBoxLayout* lucideLayout = new QVBoxLayout();
    QLabel* lucideLabel = new QLabel("Lucide动画");
    lucideLabel->setAlignment(Qt::AlignCenter);
    
    QIconKit::AnimationParams lucideParams;
    lucideParams.duration = 1800;
    lucideParams.maxScale = 1.4;
    QIconKit::AnimatedIcon* lucideIcon = AnimatedLucideIcon(
        HeartPulse, QIconKit::AnimationType::Beat, 32, Qt::darkMagenta, lucideParams);
    m_animatedIcons.append(lucideIcon);
    
    lucideLayout->addWidget(lucideLabel);
    lucideLayout->addWidget(lucideIcon, 0, Qt::AlignCenter);
    
    QVBoxLayout* fontAwesomeLayout = new QVBoxLayout();
    QLabel* fontAwesomeLabel = new QLabel("FontAwesome动画");
    fontAwesomeLabel->setAlignment(Qt::AlignCenter);
    
    QIconKit::AnimationParams faParams;
    faParams.shakeAmount = 10.0;
    QIconKit::AnimatedIcon* faIcon = AnimatedFontAwesomeIcon(
        Bell, QIconKit::AnimationType::Shake, 32, Qt::darkMagenta, faParams);
    m_animatedIcons.append(faIcon);
    
    fontAwesomeLayout->addWidget(fontAwesomeLabel);
    fontAwesomeLayout->addWidget(faIcon, 0, Qt::AlignCenter);
    
    animGrid->addLayout(materialLayout, row, col++);
    animGrid->addLayout(lucideLayout, row, col++);
    animGrid->addLayout(fontAwesomeLayout, row, col++);
    
    animMainLayout->addLayout(animGrid);
    
    // 添加动画组到主布局
    contentLayout->addWidget(animGroup);
    
    // 添加一些说明信息
    QLabel* infoLabel = new QLabel("动画图标可以应用于通知、加载状态、按钮反馈等场景");
    infoLabel->setAlignment(Qt::AlignCenter);
    infoLabel->setStyleSheet("color: gray;");
    contentLayout->addWidget(infoLabel);
    
    // 添加按钮附加示例
    QGroupBox* attachedButtonGroup = new QGroupBox("附加动画图标到按钮", m_contentWidget);
    QVBoxLayout* attachedButtonLayout = new QVBoxLayout(attachedButtonGroup);
    
    QLabel* buttonInfoLabel = new QLabel("这些按钮的图标由AnimatedIcon控制：");
    attachedButtonLayout->addWidget(buttonInfoLabel);
    
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    
    // 创建几个不同的按钮和动画图标
    // 旋转加载图标
    QPushButton* loadButton = new QPushButton("加载中");
    QIconKit::AnimatedIcon* spinIcon = AnimatedRemixIcon(
        Loader4Line, QIconKit::AnimationType::Spin, 24, Qt::blue);
    spinIcon->attachToButton(loadButton); // 附加到按钮
    m_animatedIcons.append(spinIcon);
    
    // 心跳通知图标
    QPushButton* notifyButton = new QPushButton("新通知");
    QIconKit::AnimationParams beatParams;
    beatParams.duration = 1500;
    QIconKit::AnimatedIcon* beatIcon = AnimatedRemixIcon(
        NotificationFill, QIconKit::AnimationType::Beat, 24, Qt::red, beatParams);
    beatIcon->attachToButton(notifyButton); // 附加到按钮
    m_animatedIcons.append(beatIcon);
    
    // 闪烁警告图标
    QPushButton* warningButton = new QPushButton("警告");
    QIconKit::AnimationParams blinkParams;
    blinkParams.duration = 1000;
    QIconKit::AnimatedIcon* blinkIcon = AnimatedRemixIcon(
        AlarmWarningFill, QIconKit::AnimationType::Blink, 24, Qt::yellow, blinkParams);
    blinkIcon->attachToButton(warningButton); // 附加到按钮
    m_animatedIcons.append(blinkIcon);
    
    // 添加到布局
    buttonsLayout->addWidget(loadButton);
    buttonsLayout->addWidget(notifyButton);
    buttonsLayout->addWidget(warningButton);
    attachedButtonLayout->addLayout(buttonsLayout);
    
    // 添加说明
    QLabel* noteLabel = new QLabel("注意：按钮仍然可以正常交互，点击事件不受影响");
    noteLabel->setStyleSheet("color: gray;");
    attachedButtonLayout->addWidget(noteLabel);
    
    // 添加到主布局
    contentLayout->addWidget(attachedButtonGroup);
}

// 控制所有动画的方法
void QtWidgetSample::startAllAnimations() {
    for (auto* icon : m_animatedIcons) {
        icon->start();
    }
}

void QtWidgetSample::stopAllAnimations() {
    for (auto* icon : m_animatedIcons) {
        icon->stop();
    }
}

void QtWidgetSample::pauseAllAnimations() {
    for (auto* icon : m_animatedIcons) {
        icon->pause();
    }
}

void QtWidgetSample::resumeAllAnimations() {
    for (auto* icon : m_animatedIcons) {
        icon->resume();
    }
} 