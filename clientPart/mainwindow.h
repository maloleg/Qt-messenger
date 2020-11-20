#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientStuff.h"
#include <QPixmap>
#include <QBuffer>
#include <QThread>


namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void setStatus(bool newStatus);
    void receivedJson(QJsonObject message);
    void gotError(QAbstractSocket::SocketError err);

private slots:
    void on_pushButton_send_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_enterDialog_clicked();
    void on_pushButton_sendPicture_clicked();
    void getUsers();
    void getImage(int id, const QImage& image);
    void SendFrame();

private:
    Ui::MainWindow *ui;
    ClientStuff *client;
    QString name;
    QString withWho;
    QCamera* camera;
    QCameraViewfinder* viewfinder;
    QCameraImageCapture* imageCapture;
    QTimer* timer;
};

#endif // MAINWINDOW_H
