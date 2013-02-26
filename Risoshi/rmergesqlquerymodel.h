#ifndef RMERGESQLQUERYMODEL_H
#define RMERGESQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QList>
#include <QMap>

class RMergeSqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT
public:
    explicit RMergeSqlQueryModel(QObject *parent = 0);
    void addExcluded(int column, QString value);
    void clearExcluded();


    QVariant data(const QModelIndex &item, int role = Qt::DisplayRole) const;


signals:
    
public slots:

private:
    QList< QPair<int, QString> > excluded;
    QList<int> excludedRows;
};

#endif // RMERGESQLQUERYMODEL_H
