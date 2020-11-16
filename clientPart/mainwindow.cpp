#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_disconnect->setVisible(false);

    client = new ClientStuff("localhost", 6547);

    setStatus(client->getStatus());

    connect(client, &ClientStuff::hasReadSome, this, &MainWindow::receivedSomething);
    connect(client, &ClientStuff::statusChanged, this, &MainWindow::setStatus);

    connect(ui->pushButton_dialogWith, &QPushButton::clicked, this, &MainWindow::on_pushButton_enterDialog_clicked);
    // connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::on_pushButton_send_clicked);

    // FIXME change this connection to the new syntax
    connect(client->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(gotError(QAbstractSocket::SocketError)));

    connect(ui->pushButtonGetUsers, &QPushButton::clicked, this, getUsers());
}

MainWindow::~MainWindow()
{
    delete client;
    delete ui;
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

void MainWindow::receivedSomething(QString msg)
{
    ui->textEdit_log->append(msg);
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

void getUsers(){
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
 
    QJsonObject message;
    message["type"] = "getUsers";
    // message["name"] = ui->lineEdit->text();
    // message["dialogWith"] = ui->lineEdit_2->text();
    // message["friend"] = withWho;   

    qDebug() << message;    
    
    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);
}