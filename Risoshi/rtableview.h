#ifndef RTABLEVIEW_H
#define RTABLEVIEW_H

#include <QTableView>
#include <QSignalMapper>
#include <QMenu>


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
    void menuAction(const QString &);
    void addRow( );
    void editRow(int row);
    void removeRow( int );

private:
    QMenu menu;
    enum MenuEntries { mAdd, mEdit, mRemove, mLast };
    QAction* actions[mLast];

    QSignalMapper mapper;
};

#endif // RTABLEVIEW_H
