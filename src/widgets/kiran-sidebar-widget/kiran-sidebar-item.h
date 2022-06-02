#pragma once

#include <QListWidgetItem>

class KiranSidebarItem : public QListWidgetItem
{
public:
    explicit KiranSidebarItem(QListWidget *view = nullptr, int type = Type);
    explicit KiranSidebarItem(const QString &text, QListWidget *view = nullptr, int type = Type);
    explicit KiranSidebarItem(const QIcon &icon, const QString &text,
                              QListWidget *view = nullptr, int type = Type);
    KiranSidebarItem(const QListWidgetItem &other);
    virtual ~KiranSidebarItem();

    void setStatusDesc(const QString &desc, QColor &color);
    void getStatusDesc(QString &desc, QColor &color);
};