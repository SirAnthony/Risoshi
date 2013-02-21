#include "rfilewidget.h"
#include "ui_rfilewidget.h"
#include <QtGui>
#include <QFileDialog>
#include <QFileInfo>


RFileWidget::RFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RFileWidget)
{
    ui->setupUi(this);
}

RFileWidget::~RFileWidget()
{
    delete ui;
}

QString RFileWidget::save( QString name )
{
    QFile sourceFile(ui->fileEdit->text());
    QFileInfo sourceInfo(sourceFile);

    if( name == "" || !sourceFile.exists() ){
        qDebug() << "Cannot create file '" << name << "'.\n"
                 << "Name is empty or file '" << sourceInfo.absolutePath() << "' does not exists.";
        return "";
    }

    QString papersDir = "papers";
    if( !QDir().exists(papersDir) )
        QDir().mkdir(papersDir);

    QFileInfo output = QDir(papersDir).filePath(name + "." + sourceInfo.suffix());

    if( output.filePath() != sourceInfo.filePath() &&
        !output.exists() && sourceFile.size() != output.size() ){
        sourceFile.copy(output.filePath());
        if( !ui->saveOriginal->isChecked() )
            sourceFile.remove();
    }

    ui->fileEdit->setText( output.filePath() );
    return QDir::fromNativeSeparators( output.filePath() );
}

void RFileWidget::load(QString name)
{
    ui->fileEdit->setText( QDir::toNativeSeparators( name ) );
}

void RFileWidget::browse()
{
    QString name = QFileDialog::getOpenFileName(this,
         tr("Open paper"), lastDir, tr("Documents (*.pdf *.djvu)"));
    if( name == "" )
        return;
    QFileInfo fi = name;
    lastDir = fi.absoluteDir().absolutePath();
    ui->fileEdit->setText( name );
}
