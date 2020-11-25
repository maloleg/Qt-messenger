#include "clientStuff.h"

ClientStuff::ClientStuff(
        const QString hostAddress,
        int portNumber,
        QObject *parent
        ) : QObject(parent), m_nNextBlockSize(0)
{


    status = false;

    host = hostAddress;
    port = portNumber;

    tcpSocket = new QTcpSocket(this);
    connect(tcpSocket, &QTcpSocket::disconnected, this, &ClientStuff::closeConnection);

    timeoutTimer = new QTimer();
    timeoutTimer->setSingleShot(true);
    connect(timeoutTimer, &QTimer::timeout, this, &ClientStuff::connectionTimeout);
}

void ClientStuff::connect2host()
{
    timeoutTimer->start(3000);

    tcpSocket->connectToHost(host, port);
    connect(tcpSocket, &QTcpSocket::connected, this, &ClientStuff::connected);
    connect(tcpSocket, &QTcpSocket::readyRead, this, &ClientStuff::readyRead);
}

void ClientStuff::connectionTimeout()
{
    //qDebug() << tcpSocket->state();
    if(tcpSocket->state() == QAbstractSocket::ConnectingState)
    {
        tcpSocket->abort();
        emit tcpSocket->error(QAbstractSocket::SocketTimeoutError);
    }
}

void ClientStuff::connected()
{
    status = true;
    emit statusChanged(status);
}

bool ClientStuff::getStatus() {return status;}

void ClientStuff::readyRead(){
    QDataStream in(tcpSocket);
    QByteArray byteMessage;
    m_nNextBlockSize = 0;
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        // if (!m_nNextBlockSize)
        // {
        //     if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
        //     in >> m_nNextBlockSize;
        // }

        // if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }

        // QJsonDocument str; 

        // while (tcpSocket->bytesAvailable() > 0){
        //     qDebug() << "bytes to read: " << tcpSocket->bytesAvailable() <<  m_nNextBlockSize << byteMessage.size();
        //     in >> byteMessage;
        //     // if (in.commitTransaction()){}

        //  }

        // qDebug() << "byteMessage size: " << byteMessage.size() << "  " << m_nNextBlockSize;

        // // if (str == "0")
        // // {
        // //     str = "Connection closed";
        // //     closeConnection();
        // // }
        // QJsonParseError parseError;

        // emit hasReadSome(QJsonDocument::fromJson(byteMessage, &parseError).object());
        // m_nNextBlockSize = 0;

        //--------------------------------------------------------
        in.startTransaction();
        if (!m_nNextBlockSize) {
                if (tcpSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        // message;
        // qDebug() << clientSocket->bytesAvailable();
        // if (clientSocket->bytesAvailable() > )
         while (tcpSocket->bytesAvailable() > 0){
            qDebug() << "bytes to read: " << tcpSocket->bytesAvailable() <<  m_nNextBlockSize << byteMessage.size();
            // if (tcpSocket->bytesAvailable() > 20000000){
            //     qDebug() << "flushing socket...";
            //     // tcpSocket->flush();
            //     continue;
            // }
            /*(if (clientSocket->waitForReadyRead()) */ in >> byteMessage;
            // if (in.commitTransaction()){}

         }
            // qDebug

        qDebug() << byteMessage.size();

        if (in.commitTransaction()) {
            // in.abortTransaction();
            // qDebug() << "We made it";
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // qDebug() << byteMessage;
            // we try to create a json document with the data we received
            const QJsonDocument jsonMessage = QJsonDocument::fromJson(byteMessage, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonMessage.isObject()){ // and is a JSON object
                    qDebug() << "jsonReceived  size:" << byteMessage.size();
                    emit hasReadSome(jsonMessage.object()); // send the message to the central server
                }
                else
                    qDebug() << ("Invalid message: " + QString::fromUtf8(byteMessage)); //notify the server of invalid data
            } else {
                emit qDebug() << ("Invalid message: " + QString::fromUtf8(byteMessage)); //notify the server of invalid data
            }
             // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            m_nNextBlockSize = 0;
            break;
        }


        // emit gotNewMesssage(message["type"]);

        m_nNextBlockSize = 0;
    }
}

//void ClientStuff::gotDisconnection()
//{
//    status = false;
//    emit statusChanged(status);
//}

void ClientStuff::closeConnection()
{
    timeoutTimer->stop();

    //qDebug() << tcpSocket->state();
    disconnect(tcpSocket, &QTcpSocket::connected, 0, 0);
    disconnect(tcpSocket, &QTcpSocket::readyRead, 0, 0);

    bool shouldEmit = false;
    switch (tcpSocket->state())
    {
        case 0:
            tcpSocket->disconnectFromHost();
            shouldEmit = true;
            break;
        case 2:
            tcpSocket->abort();
            shouldEmit = true;
            break;
        default:
            tcpSocket->abort();
    }

    if (shouldEmit)
    {
        status = false;
        emit statusChanged(status);
    }
}
