#include "rtableview.h"


RTableView::RTableView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RTableView)
{
    ui->setupUi(this);
}

RTableView::~RTableView()
{
    delete ui;
}
