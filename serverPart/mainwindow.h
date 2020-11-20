#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include <QMainWindow>
#include <QDebug>
#include <QObject>
#include "serverStuff.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QObject
{
    Q_OBJECT
    
public:
    explicit MainWindow();
    ~MainWindow();
    
private slots:
    void on_pushButton_stopServer_clicked();
    void on_pushButton_startServer_clicked();
    void on_pushButton_testConn_clicked();
    void on_pushButton_send_clicked();
    void smbConnectedToServer();
    void smbDisconnectedFromServer();
    void gotNewMesssage(QString msg);

private:
    // Ui::MainWindow *ui;
    ServerStuff *server;
};

#endif // MAINWINDOW_H
