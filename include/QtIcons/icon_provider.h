//
// Created by Yang1206 on 2025/3/2.
//

#ifndef ICON_PROVIDER_H
#define ICON_PROVIDER_H

#include <QIcon>
#include <QString>
#include <QColor>
#include "QtIcons/QtIcons_export.h"

namespace QtIcons {

class QTICONS_EXPORT IconProvider {
public:
    virtual ~IconProvider() = default;

    // 根据Unicode编码获取QIcon
    virtual QIcon iconFromCode(int iconCode, int size = 16, const QColor& color = QColor(0, 0, 0)) const = 0;

    // 获取字体名称
    virtual QString fontFamily() const = 0;

    // 加载字体
    virtual bool loadFont() = 0;
};

} // namespace QtIcons

#endif //ICON_PROVIDER_H