#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_disconnect->setVisible(false);

    camera = new QCamera;
    viewfinder = new QCameraViewfinder;

    timer = new QTimer;

    timer->setInterval(50);
    
    QCameraViewfinderSettings viewfinderSettings;
    viewfinderSettings.setResolution(160, 120);

    camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
    // viewfinder->show();

    imageCapture = new QCameraImageCapture(camera);

    camera->start();

    connect (timer, &QTimer::timeout, this, &MainWindow::SendFrame);

    connect (imageCapture, &QCameraImageCapture::imageCaptured, this, &MainWindow::getImage);

    // connect (ui->pushButton_sendPicture, &QPushButton::clicked, this, &MainWindow::on_pushButton_sendPicture_clicked);

    client = new ClientStuff("localhost", 6547);

    setStatus(client->getStatus());

    connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedJson);
    connect(client, &ClientStuff::statusChanged, this, &MainWindow::setStatus);

    connect(ui->pushButton_dialogWith, &QPushButton::clicked, this, &MainWindow::on_pushButton_enterDialog_clicked);
    // connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::on_pushButton_send_clicked);

    // FIXME change this connection to the new syntax
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));

    connect(ui->pushButtonGetUsers, &QPushButton::clicked, this, &MainWindow::getUsers);
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
    delete camera;
    delete viewfinder;
    delete imageCapture;
    delete timer;
}

void MainWindow::setStatus(bool newStatus)
{
    if(newStatus)
    {
        ui->label_status->setText(
                    tr("<font color=\"green\">CONNECTED</font>"));
        ui->pushButton_connect->setVisible(false);
        ui->pushButton_disconnect->setVisible(true);



        //send ip and port
        QByteArray arrBlock;
        QDataStream out(&arrBlock, QIODevice::WriteOnly);
        //out.setVersion(QDataStream::Qt_5_10);
        // const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        // for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        //     if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        //         // qDebug() << address.toString();
        //         out << quint16(0) << address.toString();
        //     // out.device()->seek(0);
        //     // out << quint16(arrBlock.size() - sizeof(quint16));

            // client->tcpSocket->write(arrBlock);
        // }
        QJsonObject message;
        message["type"] = "Login";
        message["name"] = ui->lineEdit->text();
        // message["friend"] = withWho;   

        qDebug() << message;    
        
        out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);
    // QByteArray arrBlock;
    // QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
        // out << quint16(0) << name;
        // out << quint16(0) << withWho;

        out.device()->seek(0);
        out << quint16(arrBlock.size() - sizeof(quint16));

        client->tcpSocket->write(arrBlock);


    }
    else
    {
        ui->label_status->setText(
                tr("<font color=\"red\">DISCONNECTED</font>"));
        ui->pushButton_connect->setVisible(true);
        ui->pushButton_disconnect->setVisible(false);
    }
}

void MainWindow::receivedJson(QJsonObject message)
{
    // ui->textEdit_log->append(msg);
    qDebug() << "JSON RECIEVED: " << QJsonDocument(message).toJson(QJsonDocument::Compact).size() << "bytes";
    if  (message["type"].toString() == "message"){
        ui->textEdit_log->append(message["name"].toString() + ": " + message["text"].toString());
    }
    else if (message["type"].toString() == "FromServer"){
        ui->textEdit_log->append(tr("<font color=\"red\">FROM SERVER:</font>") + message["text"].toString());
    }
    else if (message["type"].toString() == "Close Connection"){
        ui->textEdit_log->append(tr("<font color=\"red\">CONNECTION CLOSED:</font>"));
    }
    else if (message["type"].toString() == "Dialog Entered"){
        ui->label_2->setText(message["name"].toString());
    }
    else if (message["type"].toString() == "image"){
        QByteArray br = message["img"].toString().toUtf8();

        // qDebug() << br << "<- base64";

        QImage im;
        QByteArray pic(br);

        // QPixmap image;
        im.loadFromData(QByteArray::fromBase64(pic));
        // ui->img_label->setPixmap(image);

        // ui->img_label->setPixmap(QPixmap::fromImage(im));
        
        

        // im.loadFromData(br);

        // qDebug() << "image" << im.size() << br.size();

        ui->img_label->setPixmap(QPixmap::fromImage(im));
        ui->img_label->setScaledContents(true);
    }
}

void MainWindow::gotError(QAbstractSocket::SocketError err)
{
    //qDebug() << "got error";
    QString strError = "unknown";
    switch (err)
    {
        case 0:
            strError = "Connection was refused";
            break;
        case 1:
            strError = "Remote host closed the connection";
            break;
        case 2:
            strError = "Host address was not found";
            break;
        case 5:
            strError = "Connection timed out";
            break;
        default:
            strError = "Unknown error";
    }

    ui->textEdit_log->append(strError);
}

void MainWindow::on_pushButton_connect_clicked()
{
    client->connect2host();
    name = ui->lineEdit->text();
    withWho = ui->lineEdit_2->text();
    
}

void MainWindow::on_pushButton_send_clicked()
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);

    QJsonObject message;
    message["type"] = "message";
    message["name"] = ui->lineEdit->text();
    message["dialogWith"] = ui->lineEdit_2->text();
    message["text"] = ui->lineEdit_message->text();

    ui->textEdit_log->append("you: " + ui->lineEdit_message->text());

    qDebug() << message;

    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}

void MainWindow::on_pushButton_enterDialog_clicked(){
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
 
    QJsonObject message;
    message["type"] = "Enter";
    message["name"] = ui->lineEdit->text();
    message["dialogWith"] = ui->lineEdit_2->text();
    // message["friend"] = withWho;   

    qDebug() << message;    
    
    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);

}

void MainWindow::on_pushButton_disconnect_clicked()
{
    client->closeConnection();
}

void MainWindow::getUsers(){
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
 
    QJsonObject message;
    message["type"] = "getUsers";
    message["name"] = ui->lineEdit->text();
    // message["name"] = ui->lineEdit->text();
    // message["dialogWith"] = ui->lineEdit_2->text();
    // message["friend"] = withWho;   

    qDebug() << message;    
    
    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}

void MainWindow::getImage(int id, const QImage& img){
    // qDebug() << image.toImageFormat();
    // qDebug() << QByteArray::fromRawData((const char*)img.bits(), img.byteCount()).size();

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);

    QByteArray ba;
    QBuffer bu(&ba);
    img.save(&bu, "PNG");
    QString imgBase64 = ba.toBase64();

    QJsonObject message;
    message["type"] = "image";
    message["name"] = ui->lineEdit->text();
    message["dialogWith"] = ui->lineEdit_2->text();
    message["img"] = imgBase64;
    // message["name"] = ui->lineEdit->text();
    // message["dialogWith"] = ui->lineEdit_2->text();
    // message["friend"] = withWho;   

    
    // qDebug() << message["img"].toString().toUtf8() << "<- base64";


    
    // qDebug() << message;    
    
    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    qDebug() << arrBlock.size() - sizeof(quint16);

    client->tcpSocket->write(arrBlock);

}

void MainWindow::on_pushButton_sendPicture_clicked(){
    // 
    // QThread::sleep(0.5);
    timer->start();
    
}

void MainWindow::SendFrame(){
    
    if (imageCapture->isReadyForCapture())  imageCapture->capture();
}