#ifndef RFILENAMEWIDGET_H
#define RFILENAMEWIDGET_H

#include <QWidget>

namespace Ui {
class RFileNameWidget;
}

class RFileNameWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RFileNameWidget(QWidget *parent = 0);    
    ~RFileNameWidget();

signals:
    void valueChanged(QString value);

private slots:
    void browse();

private:
    QString lastDir;
    Ui::RFileNameWidget *ui;
};

#endif // RFILENAMEWIDGET_H
