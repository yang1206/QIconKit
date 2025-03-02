#ifndef TWOTONEICONGRID_H
#define TWOTONEICONGRID_H

#include "icongrid.h"
#include <QColorDialog>
#include <QPushButton>
#include <functional>

class TwoToneIconGrid : public IconGrid {
    Q_OBJECT

public:
    explicit TwoToneIconGrid(QWidget* parent = nullptr);

    // 设置双色图标
    void setTwoToneIcons(const QMap<int, QString>& iconMap,
                         std::function<QIcon(int, int, const QColor&, const QColor&)> iconProvider);

    // 设置双色图标提供者
    void setTwoToneIconProvider(std::function<QIcon(int, int, const QColor&, const QColor&)> iconProvider);

    private slots:
        void selectPrimaryColor();
    void selectSecondaryColor();
    void updateIcons();

private:
    QPushButton* m_primaryColorButton;
    QPushButton* m_secondaryColorButton;
    QColor m_primaryColor;
    QColor m_secondaryColor;
    std::function<QIcon(int, int, const QColor&, const QColor&)> m_twoToneIconProvider;
};

#endif // TWOTONEICONGRID_H