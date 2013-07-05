#include <QInputDialog>
#include <QSqlError>
#include "rcategoryview.h"
#include "models.h"


static const int ItemRole = Qt::UserRole + 1;


RCategoryView::RCategoryView(QWidget *parent) :
    QTreeView(parent), current(NULL)
{
    this->setEditTriggers(QTreeView::NoEditTriggers);
    this->setModel(&categoryModel);
    clearCategories();

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


void RCategoryView::loadCategories(bool force)
{
    this->clearSelection();

    if( cloaded && !force )
        return;

    QStringList hlabels;
    hlabels.append("Categories");
    clearCategories();
    categoryModel.setHorizontalHeaderLabels(hlabels);

    DQList<Category> list = Category::objects().all();    
    int count = 0;
    while( list.size() > 0 && count != list.size() ){
        count = list.size();
        for( int i = 0 ; i < list.size(); i++ ){
            Category* c = list.at(i);
            QStandardItem* item = NULL;
            QStandardItem* parent = NULL;
            if( c->parent ){
                QMap<int, QStandardItem*>::const_iterator it = categories.find(c->parent->id);
                if( it == categories.end() )
                    continue; // Item not created yet. Infinity loop if base corrupted.
                parent = *it;
            }

            item = new QStandardItem(QString(c->title));
            item->setData(c->id, ItemRole);

            if(parent)
                parent->appendRow(item);
            else
                categoryModel.appendRow(item);

            categories[c->id] = item;

            list.removeAt(i--);
        }
    }

    if( list.size() ){
        qDebug() << count << "categories orphaned.";
        for( int i = 0 ; i < list.size(); i++ ){
            Category* c = list.at(i);
            QStandardItem* item = new QStandardItem(QString(c->title) + " (orphan)");
            item->setData(c->id, ItemRole);
            categoryModel.appendRow(item);
        }
    }


    this->expandAll();
    cloaded = true;
}

void RCategoryView::clearCategories()
{
    categoryModel.clear();
    categories.clear();
    cloaded = false;
}

void RCategoryView::save(Article * item)
{
    current = item;
    if( !item )
        return;

    CategoryJoin::objects().filter(
                DQWhere("article =", item->id)).remove();

    QModelIndexList indices = this->selectionModel()->selectedRows();
    QModelIndex index;
    foreach(index, indices){
        int id = index.data(ItemRole).toInt();
        Category cat;
        cat.load(DQWhere("id =", id));
        CategoryJoin join;
        join.article = *item;
        join.category = cat;
        if( !join.save() )
            qDebug() << "Error while category saving:\n" << join.connection().lastQuery().lastError().text();
    }

    load(item);
}

void RCategoryView::load(Article * item)
{
    loadCategories();
    current = item;

    if( !item )
        return;

    QItemSelectionModel* selModel = this->selectionModel();

    DQList<CategoryJoin> list = CategoryJoin::objects().filter(
                DQWhere("article =", item->id)).all();
    for( int i = 0 ; i < list.size(); i++ ){
        CategoryJoin* join = list.at(i);
        QMap<int, QStandardItem*>::const_iterator it = categories.find(join->category->id);
        if( it == categories.end() ){
            qDebug() << "Category " << join->category->title << "was not found";
            continue;
        }

        selModel->select(it.value()->index(), QItemSelectionModel::Select);
    }
}

void RCategoryView::contextMenuShow(const QPoint & pos)
{
    // Change item
    int id = 0;
    QModelIndex index = this->indexAt( pos );
    if( index.isValid() )
        id = index.data(ItemRole).toInt();

    for( int var = 0; var < mLast; ++var ){
        actions[var]->setVisible( !var || id > 0 );
        mapper.setMapping( actions[var], QString("%1-%2").arg(var).arg(id) );
    }

    menu.exec( mapToGlobal(pos) );
}

void RCategoryView::menuAction(const QString &str)
{
    QStringList tmp = str.split("-");
    int entry = tmp.at(0).toInt();
    int id = tmp.at(1).toInt();
    switch( entry ){
        case mAdd:
            emit addItem(id);
            break;
        case mEdit:
            emit editItem(id);
            break;
        case mRemove:
            emit removeItem(id);
            break;
    }
}

void RCategoryView::addItem(int id)
{
    bool ok;
    Category parent;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Category name:"), QLineEdit::Normal,
                                            QString(""), &ok);
    if( !ok || text.isEmpty())
        return;

    QMap<int, QStandardItem*>::const_iterator it = categories.find(id);
    if( it != categories.end() ){
        parent.load(DQWhere("id =", id));
    }


    Category current;
    current.title = text;
    if(parent.id){
        current.parent = parent;
    }

    if( current.save() )
        loadCategories(true);
        return;

    qDebug() << "Error while category saving:\n" << current.connection().lastQuery().lastError().text();
}


void RCategoryView::editItem(int id)
{
    QStandardItem* item = NULL;
    QMap<int, QStandardItem*>::const_iterator it = categories.find(id);
    if( it != categories.end() )
        item = *it;

    if( !item )
        return;

    QString itext = item->text();

    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                            tr("Category name:"), QLineEdit::Normal,
                                            itext, &ok);
    if( !ok || text == itext)
        return;

    Category current;
    current.load(DQWhere("id =", id));
    if( !current.id )
        return;

    current.title = text;

    if( current.save() )
        loadCategories(true);
        return;

    qDebug() << "Error while category saving:\n" << current.connection().lastQuery().lastError().text();

}

void RCategoryView::removeItem(int id)
{
    Category current;
    current.load(DQWhere("id =", id));
    if( !current.id )
        return;

    CategoryJoin::objects().filter(
                DQWhere("category =", id)).remove();

    if( current.remove() )
        loadCategories(true);
        return;

    qDebug() << "Error while category saving:\n" << current.connection().lastQuery().lastError().text();
}
