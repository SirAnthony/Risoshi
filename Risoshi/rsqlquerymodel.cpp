#include "rsqlquerymodel.h"

RSqlQueryModel::RSqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
    current = NULL;
}

Article *RSqlQueryModel::getCurrent()
{
    return current;
}


void RSqlQueryModel::setCurrent( int id )
{
    this->clearCurrent();
    current = new Article();
    current->load( DQWhere("id") == id );
}


void RSqlQueryModel::clearCurrent()
{
    if( !current )
        return;
    delete current, current = NULL;
}


void RSqlQueryModel::removeCurrent()
{
    if( !current )
        return;
    current->remove();
    this->clearCurrent();
}



void RSqlQueryModel::update()
{
    this->setQuery( "SELECT title,link,mag,volume,issue,year,file,abstract FROM Article;" );
    while( this->canFetchMore() )
        this->fetchMore();
}
