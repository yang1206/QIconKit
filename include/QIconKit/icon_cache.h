//
// Created by yang1206 on 2025/3/3.
//

#ifndef ICON_CACHE_H
#define ICON_CACHE_H

#include <QIcon>
#include <QColor>
#include <QMap>
#include <QString>
#include <QMutex>
#include "QIconKit/QIconKit_export.h"

namespace QIconKit {

class QICONKIT_EXPORT IconCache {
public:
    static IconCache& instance();

    // 获取图标，如果缓存中不存在则返回空图标
    QIcon getIcon(const QString& fontFamily, int iconCode, int size, const QColor& color);
    // 添加图标到缓存
    void addIcon(const QString& fontFamily, int iconCode, int size, const QColor& color, const QIcon& icon);

    // 清除缓存
    void clearCache();

    // 设置最大缓存大小
    void setMaxCacheSize(int size);

    // 获取当前缓存大小
    int cacheSize() const;

private:
    IconCache();
    ~IconCache();

    // 缓存键结构
    struct IconKey {
        QString fontFamily;
        int iconCode;
        int size;
        QColor color;

        bool operator<(const IconKey& other) const;
    };

    mutable QMutex m_mutex; // 用于线程安全
    QMap<IconKey, QIcon> m_iconCache;
    int m_maxCacheSize = 1000; // 默认最大缓存1000个图标
};

}

#endif //ICON_CACHE_H
