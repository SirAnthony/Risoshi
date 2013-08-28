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


void RSqlQueryModel::setCurrent( QString name )
{
    this->clearCurrent();
    current = new Article();
    current->load( DQWhere("title") == name );
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
    this->setQuery( "SELECT id," + fields + " FROM Article;" );
    while( this->canFetchMore() )
        this->fetchMore();
}
