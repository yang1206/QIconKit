//
// Created by yang1206 on 2025/3/3.
//

#include "QIconKit/icon_cache.h"

namespace QIconKit {

bool IconCache::IconKey::operator<(const IconKey& other) const {
    if (fontFamily != other.fontFamily)
        return fontFamily < other.fontFamily;
    if (iconCode != other.iconCode)
        return iconCode < other.iconCode;
    if (size != other.size)
        return size < other.size;
    return color.rgba() < other.color.rgba();
}

IconCache& IconCache::instance() {
    static IconCache cache;
    return cache;
}

IconCache::IconCache() : m_maxCacheSize(1000) {
}

IconCache::~IconCache() {
    clearCache();
}

QIcon IconCache::getIcon(const QString& fontFamily, int iconCode, int size, const QColor& color) {
    QMutexLocker locker(&m_mutex);

    // 创建缓存键
    IconKey key{fontFamily, iconCode, size, color};

    // 检查缓存中是否已存在
    auto it = m_iconCache.find(key);
    if (it != m_iconCache.end()) {
        return it.value();
    }

    // 如果不存在，返回空图标
    return QIcon();
}

void IconCache::addIcon(const QString& fontFamily, int iconCode, int size, const QColor& color, const QIcon& icon) {
    QMutexLocker locker(&m_mutex);

    // 创建缓存键
    IconKey key{fontFamily, iconCode, size, color};

    // 如果缓存已满，移除最早添加的项
    if (m_iconCache.size() >= m_maxCacheSize && m_maxCacheSize > 0) {
        m_iconCache.erase(m_iconCache.begin());
    }

    // 将新图标添加到缓存
    m_iconCache.insert(key, icon);
}

void IconCache::clearCache() {
    QMutexLocker locker(&m_mutex);
    m_iconCache.clear();
}

void IconCache::setMaxCacheSize(int size) {
    QMutexLocker locker(&m_mutex);
    m_maxCacheSize = size;

    // 如果新的缓存大小小于当前缓存项数，移除多余项
    while (m_iconCache.size() > m_maxCacheSize && m_maxCacheSize > 0) {
        m_iconCache.erase(m_iconCache.begin());
    }
}

int IconCache::cacheSize() const {
    QMutexLocker locker(&m_mutex);
    return m_iconCache.size();
}

} // namespace QIconKit