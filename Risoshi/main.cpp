#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>


void message_output(QtMsgType type, const char *msg)
{
    QString types[5] = { "Debug", "Warning", "Critical", "Fatal", "System" };
    enum QtMsgType { QtDebugMsg, QtWarningMsg, QtCriticalMsg, QtFatalMsg, QtSystemMsg = QtCriticalMsg };
    QMessageBox::information( NULL, "Error", types[type] + ":\n" + msg, QMessageBox::Ok );
}



int main(int argc, char *argv[])
{
    qInstallMsgHandler(message_output);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
