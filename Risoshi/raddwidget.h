#ifndef RADDWIDGET_H
#define RADDWIDGET_H

#include <QWidget>

namespace Ui {
class RAddWidget;
}

class RAddWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RAddWidget(QWidget *parent = 0);
    ~RAddWidget();

private slots:
    void save();
    void clear();

private:
    Ui::RAddWidget *ui;
    bool newRecord;
};

#endif // RADDWIDGET_H
