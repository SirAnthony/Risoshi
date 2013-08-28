#include "raddwidget.h"
#include "ui_raddwidget.h"
#include "utils.h"
#include <QSqlError>
#include <QShortcut>


QString capitalize( const QString & str )
{
    return str.left(1).toUpper()+str.mid(1).toLower();
}


RAddWidget::RAddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RAddWidget)
{
    ui->setupUi(this);
    Model = NULL;

    QShortcut* shortcut = new QShortcut(QKeySequence(tr("Ctrl+S", "Record|Save")), this);
    connect( shortcut, SIGNAL(activated()), this, SLOT(save()) );
    shortcut->setContext( Qt::WidgetWithChildrenShortcut );

    foreach( QString item, Types )
        ui->typeEdit->addItem(item);
    ui->typeEdit->setCurrentIndex(index_from_type("article"));
}

RAddWidget::~RAddWidget()
{
    delete ui;
}

void RAddWidget::setModel(RSqlQueryModel *m)
{
    Model = m;
}

RSqlQueryModel *RAddWidget::model() const
{
    return Model;
}

void RAddWidget::load()
{
    if( !Model ){
        qDebug() << "Model was not set.";
        return;
    }

    Article* current = Model->getCurrent();
    if( current == NULL ){
        this->clear();
    }else{
        ui->titleEdit->setText(current->title);
        ui->authorsEdit->setText(current->authors);
        ui->typeEdit->setCurrentIndex(index_from_type(current->type));
        ui->linkEdit->setText(current->link);
        ui->magEdit->setText(current->mag);
        ui->volumeEdit->setValue(current->volume);
        ui->issueEdit->setValue(current->issue);
        ui->yearEdit->setValue(current->year);
        ui->firstpageEdit->setValue(current->first_page);
        ui->lastpageEdit->setValue(current->last_page);
        ui->keywordsEdit->setText(current->keywords);
        ui->abstractEdit->setPlainText(current->abstract);
        ui->fileEdit->load(current->file);
    }

    emit ui->categoryWidget->load(current);
}

void RAddWidget::save()
{
    if( !Model ){
        qDebug() << "Model was not set.";
        return;
    }

    Article* current = Model->getCurrent();

    if( current == NULL )
        current = new Article();

    QString title = capitalize(ui->titleEdit->text().trimmed());
    QString mag = capitalize(ui->magEdit->text().trimmed());
    int year = ui->yearEdit->value();

    current->title = title;    
    current->authors = ucfirst(ui->authorsEdit->text().toLower()).trimmed();
    current->link = ui->linkEdit->text().trimmed();
    current->type = Types[ui->typeEdit->currentIndex()];
    current->mag = mag;
    current->volume = ui->volumeEdit->value();
    current->issue = ui->issueEdit->value();
    current->year = year;
    current->first_page = ui->firstpageEdit->value();
    current->last_page = ui->lastpageEdit->value();
    current->keywords = ucfirst(ui->keywordsEdit->text()).trimmed();
    current->abstract = ui->abstractEdit->toPlainText().trimmed();

    QString filename = ui->fileEdit->save( title.left(60) + "_" + mag.left(15) + "_" + QString::number(year) );
    if( filename != "" )
        current->file = filename;


    if( current->save() ){
        emit ui->categoryWidget->save(current);
        return;
    }

    qDebug() << "Error while article saving:\n" << current->connection().lastQuery().lastError().text();
    //qDebug() << current->connection().lastQuery().lastQuery();
    //qDebug() << current->connection().lastQuery().boundValues();
    //qDebug() << "Error type: " << current->connection().lastQuery().lastError().type();
}

void RAddWidget::clear()
{
    if( Model )
        Model->clearCurrent();

    emit ui->categoryWidget->load(NULL);

    ui->titleEdit->clear();
    ui->authorsEdit->clear();
    ui->linkEdit->clear();
    ui->typeEdit->setCurrentIndex(index_from_type("article"));
    ui->magEdit->clear();
    ui->volumeEdit->setValue(1);
    ui->issueEdit->setValue(1);
    ui->yearEdit->setValue(2000);
    ui->firstpageEdit->setValue(1);
    ui->lastpageEdit->setValue(1);
    ui->keywordsEdit->clear();
    ui->abstractEdit->clear();
    ui->fileEdit->load("");
}
