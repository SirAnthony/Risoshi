#ifndef RFILEWIDGET_H
#define RFILEWIDGET_H

#include <QWidget>

namespace Ui {
class RFileWidget;
}

class RFileWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit RFileWidget(QWidget *parent = 0);
    ~RFileWidget();
    QString save( QString name );
    void load( QString name );

private slots:
    void browse();
    
private:
    QString lastDir;
    Ui::RFileWidget *ui;
};

#endif // RFILEWIDGET_H
