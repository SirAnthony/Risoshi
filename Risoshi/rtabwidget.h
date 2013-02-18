#ifndef RTABWIDGET_H
#define RTABWIDGET_H

#include <QTabWidget>
#include <QtSql>
#include <QSqlQueryModel>

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

private:
    Ui::RTabWidget *ui;    
    QSqlQueryModel viewModel;
    QSqlDatabase db;    
    DQConnection* connection;

};

#endif // RTABWIDGET_H
