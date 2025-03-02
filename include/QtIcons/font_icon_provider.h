//
// Created by Yang1206 on 2025/3/2.
//

#ifndef FONT_ICON_PROVIDER_H
#define FONT_ICON_PROVIDER_H

#include "icon_provider.h"
#include <QFont>
#include <QFontDatabase>

namespace QtIcons {

class QTICONS_EXPORT FontIconProvider : public IconProvider {
public:
    FontIconProvider(const QString& fontFamily, const QString& fontResource);
    ~FontIconProvider() override = default;

    QIcon iconFromCode(int iconCode, int size = 15, const QColor& color = QColor(0, 0, 0)) const override;
    QIcon twoToneIconFromCode(int iconCode, int size, const QColor& primaryColor, const QColor& secondaryColor) const;
    QString fontFamily() const override;
    bool loadFont() override;

protected:
    QString m_fontFamily;
    QString m_fontResource;
    int m_fontId = -1;

    // 渲染图标为QIcon的核心方法
    QIcon renderIcon(int iconCode, int size, const QColor& color) const;
    QIcon renderTwoToneIcon(int iconCode, int size, const QColor& primaryColor, const QColor& secondaryColor) const;
};

} // namespace QtIcons

#endif //FONT_ICON_PROVIDER_H