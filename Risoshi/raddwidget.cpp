#include "raddwidget.h"
#include "ui_raddwidget.h"
#include <QSqlError>
#include <QMessageBox>

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

    current->title = ui->titleEdit->text();
    current->link = ui->linkEdit->text();
    current->mag = ui->magEdit->text();
    current->volume = ui->volumeEdit->value();
    current->issue = ui->issueEdit->value();
    current->year = ui->yearEdit->value();
    current->abstract = ui->abstractEdit->toPlainText();

    if( current->save() )
        return;

    QString error = tr("Error while article saving.\n");
    error += current->connection().lastQuery().lastError().text();
    qDebug() << error;
    qDebug() << current->connection().lastQuery().lastQuery();
    qDebug() << current->connection().lastQuery().boundValues();
    qDebug() << "Error type: " << current->connection().lastQuery().lastError().type();

    QMessageBox::information( this, tr("Error"), error, QMessageBox::Ok );

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
}
