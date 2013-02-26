#ifndef RMERGEWIDGET_H
#define RMERGEWIDGET_H

#include <QWidget>
#include <QtSql>
#include "rmergesqlquerymodel.h"
#include "models.h"

namespace Ui {
class RMergeWidget;
}

class RMergeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RMergeWidget(QWidget *parent = 0);
    ~RMergeWidget();

public slots:
    void updateView(QString path);

private slots:
    void checkRecords();
    void merge();
    
private:    
    QSqlDatabase db;
    RMergeSqlQueryModel mergeModel;
    DQConnection* connection;
    Ui::RMergeWidget *ui;
    QList<Article*> mergeList;
};

#endif // RMERGEWIDGET_H
