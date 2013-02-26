#include "rmergewidget.h"
#include "ui_rmergewidget.h"
#include <dqsql.h>
#include "models.h"


RMergeWidget::RMergeWidget(QWidget *parent) :
    QWidget(parent), db(QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE", "MergeConnection"))),
    mergeModel( ), connection(NULL), ui(new Ui::RMergeWidget)
{
    ui->setupUi(this);
    ui->mergeView->setModel(&mergeModel);

}

RMergeWidget::~RMergeWidget()
{
    delete ui;
}


void RMergeWidget::updateView(QString path)
{
    mergeModel.clearExcluded();
    mergeList.clear();

    if( connection ){
        connection->close();
        delete connection, connection = NULL;
    }
    if( db.isOpen() )
        db.close();
    db.setDatabaseName(path);
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

    mergeModel.setQuery("SELECT title,link,mag,volume,issue,year,file,abstract FROM Article;", db);
    checkRecords();
}

void RMergeWidget::checkRecords()
{
    if( !connection )
        return;

    DQQuery<Article> base;

    DQList<Article> objects = Article::objects(*connection).all();
    for( int j = 0; j < objects.size(); ++j ){
        Article* object = objects.at(j);
        DQSharedQuery title_query = base.filter(DQWhere("title =", object->title));
        DQSharedQuery link_query = base.filter(DQWhere("link =", object->link));
        if( !title_query.count() && !link_query.count() ){
            Article* atc = new Article();
            atc->title = object->title;
            atc->link = object->link;
            atc->mag = object->mag;
            atc->volume = object->volume;
            atc->issue = object->issue;
            atc->year = object->year;
            atc->abstract = object->abstract;
            atc->file = object->file;
            mergeList.append(atc);
        }else{
            DQList<Article> title_objects = title_query.all();
            DQList<Article> link_objects = link_query.all();
            for( int i = 0; i < title_objects.size(); ++i ){
                Article* atc = objects.at(j);
                mergeModel.addExcluded(0, atc->title);
            }
            for( int i = 0; i < link_objects.size(); ++i ){
                Article* atc = objects.at(j);
                mergeModel.addExcluded(1, atc->link);
           }
        }
    }
}

void RMergeWidget::merge()
{
   for( int j = 0; j < mergeList.size(); ++j ){
       Article* atc = mergeList.at(j);

       if( !atc->save() )
           qDebug() << "Error while article saving:\n" << atc->connection().lastQuery().lastError().text();
       delete atc;
   }

   mergeList.clear();
   checkRecords();
}





