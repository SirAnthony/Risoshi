#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), db(QSqlDatabase::addDatabase("QSQLITE")),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db.setDatabaseName("db.sqlite");

    if( !db.open() ){
       qDebug()<<db.lastError().text();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}
