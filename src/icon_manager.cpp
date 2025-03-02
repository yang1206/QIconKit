//
// Created by Yang1206 on 2025/3/2.
//

#include "QIconKit/icon_manager.h"

namespace QIconKit {

IconManager& IconManager::instance() {
    static IconManager instance;
    return instance;
}

void IconManager::registerProvider(const QString& providerName, std::shared_ptr<IconProvider> provider) {
    if (provider) {
        m_providers[providerName] = provider;
    }
}

std::shared_ptr<IconProvider> IconManager::provider(const QString& providerName) const {
    return m_providers.value(providerName);
}

QStringList IconManager::providers() const {
    return m_providers.keys();
}

} // namespace QtIcons