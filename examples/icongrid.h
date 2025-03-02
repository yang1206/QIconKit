#ifndef ICONGRID_H
#define ICONGRID_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QLineEdit>
#include <QMap>
#include <QLabel>
#include <functional>

class IconButton : public QPushButton {
    Q_OBJECT
public:
    explicit IconButton(int iconCode, const QString& name, QWidget* parent = nullptr);
    int iconCode() const { return m_iconCode; }
    
private slots:
    void copyIconName();
    
private:
    QString m_iconName;
    int m_iconCode;
};

class IconGrid : public QWidget {
    Q_OBJECT
public:
    explicit IconGrid(QWidget* parent = nullptr);
    
    // 设置图标集合
    void setIcons(const QMap<int, QString>& iconMap, const std::function<QIcon(int, int, const QColor&)>& iconProvider);

    void clearIcons();

    signals:
    void iconClicked(int iconCode, const QString& iconName);
    
private slots:
    void filterIcons(const QString& filter);
    
protected:
    void setupUI();

    QVBoxLayout* m_mainLayout;
    QGridLayout* m_gridLayout;
    QScrollArea* m_scrollArea;
    QWidget* m_scrollContent;
    QLineEdit* m_searchBox;
    QLabel* m_countLabel;
    QMap<QString, IconButton*> m_iconButtons;
    std::function<QIcon(int, int, const QColor&)> m_iconProvider;
};

#endif // ICONGRID_H 