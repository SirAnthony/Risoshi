#include "rmergesqlquerymodel.h"

RMergeSqlQueryModel::RMergeSqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent)
{
}

void RMergeSqlQueryModel::addExcluded(int column, QString value)
{
    excluded.append(QPair<int, QString>(column, value));
}

void RMergeSqlQueryModel::clearExcluded()
{
    excluded.clear();
    excludedRows.clear();
}

QVariant RMergeSqlQueryModel::data(const QModelIndex &item, int role) const
{
    QVariant ret = QSqlQueryModel::data( item, role );

    if( role == Qt::BackgroundColorRole ){
        for( int i = 0; i < excluded.count(); ++i ){
            const QPair<int, QString>& pair = excluded.at(i);
            int column = item.column();
            int row = item.row();
            if( pair.first != column ){
                if( excludedRows.contains(row) )
                    return Qt::gray;
                continue;
            }

            QString data = item.data().toString();
            QString str = pair.second;
            if( str != "" && str == data ){
                return Qt::red;
            }

        }
    }

    return ret;
}

