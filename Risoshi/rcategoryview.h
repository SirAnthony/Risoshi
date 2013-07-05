#ifndef RCATEGORYVIEW_H
#define RCATEGORYVIEW_H

#include <QTreeView>
#include <QStandardItemModel>
#include <QMenu>
#include <models.h>


class RCategoryView : public QTreeView
{
    Q_OBJECT
public:
    explicit RCategoryView(QWidget *parent = 0);
    void loadCategories(bool force = false);
    void clearCategories();
    
signals:    
    
public slots:
    void save(Article*);
    void load(Article*);
    void contextMenuShow(const QPoint &);
    void menuAction(const QString &str);
    void addItem(int);
    void editItem(int);
    void removeItem(int);

private:
    QMap<int, QStandardItem*> categories;
    QStandardItemModel categoryModel;
    bool cloaded;
    Article* current;

    QMenu menu;
    enum MenuEntries { mAdd, mEdit, mRemove, mLast };
    QAction* actions[mLast];
    QSignalMapper mapper;
};

#endif // RCATEGORYVIEW_H
