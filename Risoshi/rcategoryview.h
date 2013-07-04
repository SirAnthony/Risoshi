#ifndef RCATEGORYVIEW_H
#define RCATEGORYVIEW_H

#include <QTreeView>
#include <QStandardItemModel>


class RCategoryView : public QTreeView
{
    Q_OBJECT
public:
    explicit RCategoryView(QWidget *parent = 0);
    void loadCategories();
    
signals:
    
public slots:

private:
    QStandardItemModel categoryModel;
    
};

#endif // RCATEGORYVIEW_H
