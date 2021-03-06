#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
    // QMainWindow(parent),
    
{
    // ui->setupUi(this);

    server = new ServerStuff(this);
    connect(server, &ServerStuff::gotNewMesssage,
            this, &MainWindow::gotNewMesssage);
    connect(server->tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::smbConnectedToServer);
    connect(server, &ServerStuff::smbDisconnected,
                this, &MainWindow::smbDisconnectedFromServer);
    // connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_send_clicked);

    if (!server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        // ui->textEdit_log->append(tr("<font color=\"red\"><b>Error!</b> The port is taken by some other service.</font>"));
        return;
    }
    connect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);
    // ui->textEdit_log->append(tr("<font color=\"green\"><b>Server started</b>, port is openned.</font>"));
}

MainWindow::~MainWindow()
{
    delete server;
    // delete ui;
}

void MainWindow::on_pushButton_startServer_clicked()
{
    if (!server->tcpServer->listen(QHostAddress::Any, 6547))
    {
        // ui->textEdit_log->append(tr("<font color=\"red\"><b>Error!</b> The port is taken by some other service.</font>"));
        return;
    }
    connect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);
    // ui->textEdit_log->append(tr("<font color=\"green\"><b>Server started</b>, port is openned.</font>"));
}

void MainWindow::on_pushButton_stopServer_clicked()
{
    if(server->tcpServer->isListening())
    {
        disconnect(server->tcpServer, &QTcpServer::newConnection, server, &ServerStuff::newConnection);

        QList<QTcpSocket *> clients = server->getClients();
        QJsonObject doc;
        doc["type"] = "Close Connection";
        for(int i = 0; i < clients.count(); i++)
        {
            //server->sendToClient(clients.at(i), "Connection closed");

            server->sendToClient(clients.at(i), doc);
        }

        server->tcpServer->close();
        // ui->textEdit_log->append(tr("<b>Server stopped</b>, post is closed"));
    }
    else
    {
        // ui->textEdit_log->append(tr("<b>Error!</b> Server was not running"));
    }
}

void MainWindow::on_pushButton_testConn_clicked()
{
    if(server->tcpServer->isListening())
    {
        // ui->textEdit_log->append(
        //             QString("%1 %2")
        //             .arg("Server is listening, number of connected clients:")
        //             .arg(QString::number(server->getClients().count()))
        //             );
    }
    else
    {
        // ui->textEdit_log->append(
        //             QString("%1 %2")
        //             .arg("Server is not listening, number of connected clients:")
        //             .arg(QString::number(server->getClients().count()))
        //             );
    }
}

void MainWindow::on_pushButton_send_clicked(){

    QJsonObject message;
    message["type"] = "FromServer";
    // message["text"] = ui->lineEdit->text();

    for (int i = 0; i < server->getClients().size(); i++){
        if (server->sendToClient(server->getClients()[i], message) == -1)
            {
                qDebug() << "Some error occured";
            }
    }
}

void MainWindow::smbConnectedToServer()
{
    // ui->textEdit_log->append(tr("Somebody has connected"));
}

void MainWindow::smbDisconnectedFromServer()
{
    // ui->textEdit_log->append(tr("Somebody has disconnected"));
}

void MainWindow::gotNewMesssage(QString msg)
{
    // ui->textEdit_log->append(QString("New message: %1").arg(msg));
}
