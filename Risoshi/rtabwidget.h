#ifndef RTABWIDGET_H
#define RTABWIDGET_H

#include <QTabWidget>
#include <QtSql>
#include "rsqlquerymodel.h"

class DQConnection;


namespace Ui {
    class RTabWidget;
}

class RTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    explicit RTabWidget(QWidget *parent = 0);
    ~RTabWidget();

private slots:    
    void tabSwitch(QWidget *arg1);
    void toggleEdit();
    void toggleView();

private:
    Ui::RTabWidget *ui;    
    RSqlQueryModel viewModel;
    QSqlDatabase db;    
    DQConnection* connection;

};

#endif // RTABWIDGET_H
