#ifndef RSQLQUERYMODEL_H
#define RSQLQUERYMODEL_H

#include <QSqlQueryModel>
#include "models.h"


class RSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit RSqlQueryModel(QObject *parent = 0);

    Article* getCurrent( );
    void setCurrent( int id );
    void clearCurrent( );
    void removeCurrent( );
    
signals:
    
public slots:
    void update();

private:
    Article* current;

    
};

#endif // RSQLQUERYMODEL_H
