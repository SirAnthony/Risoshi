#include "rfilenamewidget.h"
#include "ui_rfilenamewidget.h"
#include <QFileDialog>

RFileNameWidget::RFileNameWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::RFileNameWidget)
{
    ui->setupUi(this);
}

RFileNameWidget::~RFileNameWidget()
{
    delete ui;
}

void RFileNameWidget::browse()
{
    QString name = QFileDialog::getOpenFileName(this,
         tr("Open database"), lastDir, tr("Database file (*.sqlite)"));
    if( name == "" )
        return;
    QFileInfo fi = name;
    lastDir = fi.absoluteDir().absolutePath();
    ui->fileEdit->setText( name );
    emit valueChanged(name);
}
