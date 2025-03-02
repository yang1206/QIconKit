//
// Created by Yang1206 on 2025/3/2.
//

#ifndef ICON_MANAGER_H
#define ICON_MANAGER_H

#include "icon_provider.h"
#include <QMap>
#include <memory>

namespace QIconKit {

class QICONKIT_EXPORT IconManager {
public:
    static IconManager& instance();

    // 注册图标提供者
    void registerProvider(const QString& providerName, std::shared_ptr<IconProvider> provider);

    // 获取特定提供者
    std::shared_ptr<IconProvider> provider(const QString& providerName) const;

    // 获取已注册的提供者列表
    QStringList providers() const;

private:
    IconManager() = default;
    ~IconManager() = default;

    QMap<QString, std::shared_ptr<IconProvider>> m_providers;
};

} // namespace QtIcons

#endif //ICON_MANAGER_H