#ifndef ICONBROWSER_H
#define ICONBROWSER_H

#include <QWidget>
#include <QTabWidget>
#include "icongrid.h"

class IconBrowser : public QWidget {
    Q_OBJECT
    
public:
    explicit IconBrowser(QWidget* parent = nullptr);
    
private:
    void setupUI();
    void setupRemixIcons();
    void setupLucideIcons();
    void setupFontAwesomeIcons();
    void setupMaterialIcons();
    // 这里可以添加更多图标类型的设置方法
    
    QTabWidget* m_tabWidget;
    IconGrid* m_remixIconGrid;
    IconGrid* m_lucideIconGrid;
    IconGrid* m_fontAwesomeIconGrid;
    IconGrid* m_materialFilledIconGrid;
    IconGrid* m_materialOutlinedIconGrid;
    IconGrid* m_materialRoundedIconGrid;
    IconGrid* m_materialSharpIconGrid;
    // 这里可以添加更多图标网格
};

#endif // ICONBROWSER_H 