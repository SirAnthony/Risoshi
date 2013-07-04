#ifndef RADDWIDGET_H
#define RADDWIDGET_H

#include <QWidget>
#include "rsqlquerymodel.h"

namespace Ui {
    class RAddWidget;
}

class RAddWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RAddWidget(QWidget *parent = 0);    
    ~RAddWidget();

    void setModel(RSqlQueryModel *m);
    RSqlQueryModel *model() const;


public slots:
    void load();
    void save();
    void clear();

private:    
    RSqlQueryModel *Model;    
    Ui::RAddWidget *ui;
};

#endif // RADDWIDGET_H
