#ifndef RTABLEVIEW_H
#define RTABLEVIEW_H

#include <QTableView>
#include <QSignalMapper>


class RTableView : public QTableView
{
    Q_OBJECT
    
public:
    explicit RTableView(QWidget *parent = 0);
    ~RTableView();

signals:
    void toggleEdit();

public slots:
    void contextMenuShow(const QPoint &);
    void addRow( );
    void editRow(int row);
    void removeRow( int );



private:
    QSignalMapper removemapper;
    QSignalMapper editmapper;

};

#endif // RTABLEVIEW_H
