#include "rtabwidget.h"
#include "ui_rtabwidget.h"
#include "models.h"


RTabWidget::RTabWidget(QWidget *parent) :
    QTabWidget(parent), ui(new Ui::RTabWidget),
    viewModel( ), db(QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    connection(NULL)
{
    ui->setupUi(this);
    ui->ViewTable->setModel(&viewModel);

    db.setDatabaseName("db.sqlite");

    if( !db.open() ){
       qDebug() << db.lastError().text();
       return;
    }

    // Use dquest orm
    connection = new DQConnection( );

    // Establish the connection to database. It will become the "default connection" shared by all DQModel
    connection->open(db);
    // Register a model to the connection
    connection->addModel<Article>();
    // Create table for all added model
    connection->createTables();
}


RTabWidget::~RTabWidget()
{
    if( connection ){
        connection->close();
        delete connection;
    }

    // FIXME: check for db was opened
    db.close();
    delete ui;
}
