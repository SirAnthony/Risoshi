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
    connection->addModel<Category>();
    connection->addModel<CategoryJoin>();

    mergeModel.setQuery("SELECT " + fields + " FROM Article;", db);
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
            atc->authors = object->authors;
            atc->type = object->type;
            atc->link = object->link;
            atc->mag = object->mag;
            atc->volume = object->volume;
            atc->issue = object->issue;
            atc->year = object->year;
            atc->first_page = object->first_page;
            atc->last_page = object->last_page;
            atc->keywords = object->keywords;
            atc->abstract = object->abstract;            
            atc->file = object->file;
            mergeList.append(atc);
        }else{
            DQList<Article> title_objects = title_query.all();
            DQList<Article> link_objects = link_query.all();
            for( int i = 0; i < title_objects.size(); ++i ){
                Article* atc = objects.at(j);
                mergeModel.addExcluded(cTitle - 1, atc->title);
            }
            for( int i = 0; i < link_objects.size(); ++i ){
                Article* atc = objects.at(j);
                mergeModel.addExcluded(cLink - 1, atc->link);
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

