#include "serverStuff.h"

ServerStuff::ServerStuff(QObject *pwgt) : QObject(pwgt), m_nNextBlockSize(0)
{
    tcpServer = new QTcpServer(this);
    connect(this, &ServerStuff::jsonReceived, this, &ServerStuff::handleJson);
    connect(this, &ServerStuff::connectByNames, this, &ServerStuff::slot_connectByNames);
}

QList<QTcpSocket *> ServerStuff::getClients()
{
    return clients;
}

void ServerStuff::newConnection()
{
    QTcpSocket *clientSocket = tcpServer->nextPendingConnection();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerStuff::gotDisconnection);

    clients << clientSocket;

    sendToClient(clientSocket, "Reply: connection established");
}

void ServerStuff::slot_connectByNames(QString name1, QString name2){
    qDebug() << names;
    qDebug() << clients;
    pairs[name1] = clients[names.indexOf(name2)];
    pairs[name2] = clients[names.indexOf(name1)];

    
}

bool ServerStuff::isConnected(QString name1, QString name2){
    return (pairs[name1] == clients[names.indexOf(name2)]);
}

void ServerStuff::readClient()
{
    QTcpSocket *clientSocket = (QTcpSocket*)sender();

    QDataStream in(clientSocket);
    QByteArray byteMessage;
    //in.setVersion(QDataStream::Qt_5_10);
    for (;;)
    {
        in.startTransaction();
        if (!m_nNextBlockSize) {
                if (clientSocket->bytesAvailable() < sizeof(quint16)) { break; }
            in >> m_nNextBlockSize;
        }

        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        // message;
        in >> byteMessage;

        // qDebug() << byteMessage;

        if (in.commitTransaction()) {
            // in.abortTransaction();
            // qDebug() << "We made it";
            // we successfully read some data
            // we now need to make sure it's in fact a valid JSON
            QJsonParseError parseError;
            // we try to create a json document with the data we received
            const QJsonDocument jsonMessage = QJsonDocument::fromJson(byteMessage, &parseError);
            if (parseError.error == QJsonParseError::NoError) {
                // if the data was indeed valid JSON
                if (jsonMessage.isObject()){ // and is a JSON object
                    qDebug() << "jsonReceived  " << jsonMessage.object();
                    emit jsonReceived(jsonMessage.object()); // send the message to the central server
                }
                else
                    emit gotNewMesssage("Invalid message: " + QString::fromUtf8(byteMessage)); //notify the server of invalid data
            } else {
                emit gotNewMesssage("Invalid message: " + QString::fromUtf8(byteMessage)); //notify the server of invalid data
            }
             // loop and try to read more JSONs if they are available
        } else {
            // the read failed, the socket goes automatically back to the state it was in before the transaction started
            // we just exit the loop and wait for more data to become available
            break;
        }


        // emit gotNewMesssage(message["type"]);

        m_nNextBlockSize = 0;

        // if (!in.commitTransaction())

        // if (sendToClient(clientSocket, QString("Reply: received [%1]").arg(message["type"])) == -1)
        // {
        //     qDebug() << "Some error occured";
        // }

        
    }
}

void ServerStuff::handleJson(QJsonObject message){
    // QVariantMap m = message.toVariantMap();
    // qDebug() << message["Login"].toString();
    // qDebug() << m.value("type");
    emit gotNewMesssage("WHY");

    if (message["type"].toString() == "Login"){
        // qDebug() << message[""].toString();
        emit gotNewMesssage(message["name"].toString() + " connected");
        names << message["name"].toString();
        // emit gotNewMesssage(message["friend"].toString());
    }
    else if (message["type"].toString() == "Enter"){
        if (names.contains(message["name"].toString()) && names.contains(message["dialogWith"].toString())){
            if (message["name"].toString() != message["dialogWith"].toString()){
                emit gotNewMesssage(message["name"].toString() + " connected to " + message["dialogWith"].toString());
                //connect them

                emit connectByNames(message["name"].toString(), message["dialogWith"].toString());
            }
            else emit gotNewMesssage("you cannot connect to yourself");
            
        }
        else emit gotNewMesssage("No such user");
    }
    else if (message["type"].toString() == "message"){
        if (names.contains(message["name"].toString()) && names.contains(message["dialogWith"].toString())){
            if (message["name"].toString() != message["dialogWith"].toString()){
                // emit gotNewMesssage(message["name"].toString() + " connected to " + message["dialogWith"].toString());
                //connect them
                if (isConnected(message["name"].toString(), message["dialogWith"].toString())){       
                    // qDebug() << names << names[i] << message["dialogWith"].toString();
                    qDebug() << pairs;
                    emit gotNewMesssage(message["name"].toString() + " sending [" + message["text"].toString() + "] to " + message["dialogWith"].toString());
                    if (sendToClient(pairs[message["name"].toString()], QString(message["name"].toString() + ":" + message["text"].toString())) == -1){
                        qDebug() << "Some error occured";
                        // return;
                    }
                    // return;
             
                }
                // emit connectByNames(message["name"].toString(), message["dialogWith"].toString());
            }
            else emit gotNewMesssage("you cannot connect to yourself");
            
        }
        else emit gotNewMesssage("No such user");
    }
}

void ServerStuff::gotDisconnection()
{
    for (int i = 0; i < clients.size(); i++){
        if (clients[i] == (QTcpSocket*)sender()){
            clients.removeAt(i);
            names.removeAt(i);
            emit smbDisconnected();
            return;
        }   
    }
}

qint64 ServerStuff::sendToClient(QTcpSocket* socket, QJsonObject doc)
{
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_10);
    //out << quint16(0) << QTime::currentTime() << str;
    out << quint16(0) << doc;
    qDebug() << doc;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}
