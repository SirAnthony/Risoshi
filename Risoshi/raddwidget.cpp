#include "raddwidget.h"
#include "ui_raddwidget.h"
#include <QSqlError>


RAddWidget::RAddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RAddWidget)
{
    ui->setupUi(this);
    Model = NULL;
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
        ui->linkEdit->setText(current->link);
        ui->magEdit->setText(current->mag);
        ui->volumeEdit->setValue(current->volume);
        ui->issueEdit->setValue(current->issue);
        ui->yearEdit->setValue(current->year);
        ui->abstractEdit->setPlainText(current->abstract);
        ui->fileEdit->load(current->file);
    }
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

    QString title = ui->titleEdit->text();
    QString mag = ui->magEdit->text();
    int year = ui->yearEdit->value();

    current->title = title;
    current->link = ui->linkEdit->text();
    current->mag = mag;
    current->volume = ui->volumeEdit->value();
    current->issue = ui->issueEdit->value();
    current->year = year;
    current->abstract = ui->abstractEdit->toPlainText();

    QString filename = ui->fileEdit->save( title.left(80) + "_" + mag.left(15) + "_" + QString::number(year) );
    if( filename != "" )
        current->file = filename;


    if( current->save() )
        return;

    qDebug() << "Error while article saving.\n";
    qDebug() << current->connection().lastQuery().lastError().text();
    qDebug() << current->connection().lastQuery().lastQuery();
    qDebug() << current->connection().lastQuery().boundValues();
    qDebug() << "Error type: " << current->connection().lastQuery().lastError().type();
}

void RAddWidget::clear()
{
    if( Model )
        Model->clearCurrent();

    ui->titleEdit->clear();
    ui->linkEdit->clear();
    ui->magEdit->clear();
    ui->volumeEdit->setValue(1);
    ui->issueEdit->setValue(1);
    ui->yearEdit->setValue(2000);
    ui->abstractEdit->clear();
    ui->fileEdit->load("");
}
