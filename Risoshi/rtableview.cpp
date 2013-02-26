#include "rtableview.h"
#include "rsqlquerymodel.h"
#include "rtabwidget.h"
#include <QHeaderView>
#include <QDesktopServices>

RTableView::RTableView(QWidget *parent) :
    QTableView(parent)
{
    QHeaderView* hheader = this->horizontalHeader();
    hheader->setStretchLastSection(true);
    hheader->setMinimumSectionSize(5);
    hheader->setHighlightSections(false);
    hheader->setResizeMode(QHeaderView::Interactive);

    // FIXME: Does not work.
    int hsizes[8] = { 20, 400, 100, 300, 10, 10, 30, 300 };
    for( int var = 0; var < 8; ++var ){
        hheader->resizeSection( var, hsizes[var] );
        this->setColumnWidth( var, hsizes[var] );
    }

    this->setContextMenuPolicy( Qt::CustomContextMenu );
    connect( this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(contextMenuShow(const QPoint &)) );

    // Menu
    QString menuNames[mLast] = { "Add", "Edit", "Remove" };
    for( int var = 0; var < mLast; ++var ){
        QAction* action = menu.addAction(menuNames[var]);
        connect( action, SIGNAL(triggered()), &mapper, SLOT(map()) );
        actions[var] = action;
    }

    connect( &mapper, SIGNAL(mapped(const QString &)), this, SLOT(menuAction(const QString &)) );
}

RTableView::~RTableView()
{

}

void RTableView::contextMenuShow( const QPoint& pos )
{    
    // Change item
    int row = this->rowAt( pos.y() );

    for( int var = 0; var < mLast; ++var ){
        actions[var]->setVisible( !var || row >= 0 );
        mapper.setMapping( actions[var], QString("%1-%2").arg(var).arg(row) );
    }

    menu.exec( mapToGlobal(pos) );
}

void RTableView::menuAction( const QString & str )
{
    QStringList tmp = str.split("-");
    int entry = tmp.at(0).toInt();
    int row = tmp.at(1).toInt();
    switch( entry ){
        case mAdd:
            emit addRow();
            break;
        case mEdit:
            emit editRow(row);
            break;
        case mRemove:
            emit removeRow(row);
            break;
    }
}

void RTableView::addRow()
{
    emit toggleEdit();
}

void RTableView::editRow( int row )
{
    RSqlQueryModel* model = reinterpret_cast<RSqlQueryModel*>(this->model());
    if( model == NULL )
        return;

    int id = this->model()->data(this->model()->index(row, 0)).toInt();
    model->setCurrent(id);
    emit toggleEdit();
}


void RTableView::removeRow( int row )
{
    RSqlQueryModel* model = reinterpret_cast<RSqlQueryModel*>(this->model());
    if( model == NULL )
        return;

    int id = this->model()->data(this->model()->index(row, 0)).toInt();
    model->setCurrent( id );
    model->removeCurrent();
    emit model->update();

}

void RTableView::openFile(const QModelIndex & index)
{
    int row = index.row();
    const QModelIndex& file_index = this->model()->index(row, 6);
    QDesktopServices::openUrl(QUrl("file://./" + file_index.data().toString(), QUrl::TolerantMode));
}

