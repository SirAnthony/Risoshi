#ifndef RTABLEVIEW_H
#define RTABLEVIEW_H

#include <QTableView>

namespace Ui {
class RTableView;
}

class RTableView : public QTableView
{
    Q_OBJECT
    
public:
    explicit RTableView(QWidget *parent = 0);
    ~RTableView();
    
private:
    Ui::RTableView *ui;
};

#endif // RTABLEVIEW_H
