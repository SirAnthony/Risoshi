#include "rtableview.h"
#include "rsqlquerymodel.h"
#include "rtabwidget.h"
#include <QHeaderView>
#include <QMenu>


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

    // Map mapper to row removing
    connect( &removemapper, SIGNAL(mapped(int)), this, SLOT(removeRow(int)) );
    connect( &editmapper, SIGNAL(mapped(int)), this, SLOT(editRow(int)) );
}

RTableView::~RTableView()
{

}

void RTableView::contextMenuShow( const QPoint& pos )
{
    QMenu menu;
    // Change item
    int row = this->rowAt( pos.y() );
    if( row < 0 )
        return;


    QAction* removeaction = menu.addAction("Remove");
    connect( removeaction, SIGNAL(triggered()), &removemapper, SLOT(map()) );
    removemapper.setMapping( removeaction, row );

    QAction* editaction = menu.addAction("Edit");
    connect( editaction, SIGNAL(triggered()), &editmapper, SLOT(map()) );
    editmapper.setMapping( editaction, row );

    menu.exec( mapToGlobal(pos) );
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

