#ifndef RTABLEVIEW_H
#define RTABLEVIEW_H

#include <QTableView>
#include <QSignalMapper>
#include "rsqlquerymodel.h"
#include <QMenu>


class RTableView : public QTableView
{
    Q_OBJECT

public:

    enum Columns {
        cId = 0, cTitle, cLink, cMag, cVolume, cIssue, cYear, cFile, cAbstract
    };

    explicit RTableView(QWidget *parent = 0);
    ~RTableView();
    void setModel(RSqlQueryModel *model);


signals:
    void toggleEdit();


public slots:
    void contextMenuShow(const QPoint &);
    void menuAction(const QString &);
    void addRow( );
    void editRow(int row);
    void removeRow( int );

private slots:
    void openFile(const QModelIndex&);

private:
    QMenu menu;
    enum MenuEntries { mAdd, mEdit, mRemove, mLast };
    QAction* actions[mLast];
    RSqlQueryModel* rmodel;

    QSignalMapper mapper;
};

#endif // RTABLEVIEW_H
