#include "raddwidget.h"
#include "ui_raddwidget.h"
#include "models.h"
#include <QSqlError>
#include <QMessageBox>

RAddWidget::RAddWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RAddWidget)
{
    ui->setupUi(this);
    newRecord = true;
}

RAddWidget::~RAddWidget()
{
    delete ui;
}

void RAddWidget::save()
{
    Article atc;
    atc.title = ui->titleEdit->text();
    atc.link = ui->linkEdit->text();
    atc.mag = ui->magEdit->text();
    atc.volume = ui->volumeEdit->value();
    atc.issue = ui->issueEdit->value();
    atc.year = ui->yearEdit->value();
    atc.abstract = ui->abstractEdit->toPlainText();

    if( atc.save(newRecord) )
        return;
    QString error = tr("Error while article saving.\n");
    error += atc.connection().lastQuery().lastError().text();
    qDebug() << error;
    qDebug() << atc.connection().lastQuery().lastQuery();
    qDebug() << atc.connection().lastQuery().boundValues();
    qDebug() << "Error type: " << atc.connection().lastQuery().lastError().type();

    QMessageBox::information( this, tr("Error"), error, QMessageBox::Ok );

}

void RAddWidget::clear()
{
    ui->titleEdit->clear();
    ui->linkEdit->clear();
    ui->magEdit->clear();
    ui->volumeEdit->setValue(1);
    ui->issueEdit->setValue(1);
    ui->yearEdit->setValue(2000);
    ui->abstractEdit->clear();
}
