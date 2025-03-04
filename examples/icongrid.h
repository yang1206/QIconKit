#ifndef ICONGRID_H
#define ICONGRID_H

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
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
    int     m_iconCode;
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
    void onPageChanged(int page);

  private:
    static const int ICONS_PER_PAGE = 104;

    void setupUI();
    void clearCurrentPageButtons();

    QVBoxLayout*                                  m_mainLayout;
    QGridLayout*                                  m_gridLayout;
    QScrollArea*                                  m_scrollArea;
    QWidget*                                      m_scrollContent;
    QLineEdit*                                    m_searchBox;
    QLabel*                                       m_countLabel;
    QMap<int, IconButton*>                        m_currentPageButtons;
    QVector<QPair<int, QString>>                  m_originalIcons;
    std::function<QIcon(int, int, const QColor&)> m_iconProvider;

    QTimer* m_searchTimer;

    // 分页相关
    QHBoxLayout*                 m_paginationLayout;
    QPushButton*                 m_prevButton;
    QPushButton*                 m_nextButton;
    QLabel*                      m_pageLabel;
    QVector<QPair<int, QString>> m_filteredIcons; // 存储过滤后的图标数据
    int                          m_currentPage;
    int                          m_totalPages;
};

#endif // ICONGRID_H