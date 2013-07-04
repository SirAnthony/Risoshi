#include "rcategoryview.h"
#include "models.h"

RCategoryView::RCategoryView(QWidget *parent) :
    QTreeView(parent)
{
    this->setModel(&categoryModel);
    this->loadCategories();
}

void RCategoryView::loadCategories()
{
    DQList<Category> list = Category::objects().all();
    QMap<int, QStandardItem*> items;
    while( list.size() > 0 ){
        for( int i = 0 ; i < list.size(); i++ ){
            Category* c = list.at(i);
            QStandardItem* item = NULL;
            QStandardItem* parent = NULL;
            if( c->parent ){
                QMap<int, QStandardItem*>::const_iterator it = items.find(c->parent->id);
                if( it == items.end() )
                    continue; // Item not created yet. Infinity loop if base corrupted.
                parent = *it;
            }

            item = new QStandardItem(QString(c->title));

            if(parent)
                parent->appendRow(item);
            else
                categoryModel.appendRow(item);

            list.removeAt(i--);
        }
    }

}
