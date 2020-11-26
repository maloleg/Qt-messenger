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

    // clientSocket->setReadBufferSize(500000);

    qDebug() << clientSocket->readBufferSize();

    connect(clientSocket, &QTcpSocket::disconnected, clientSocket, &QTcpSocket::deleteLater);
    connect(clientSocket, &QTcpSocket::readyRead, this, &ServerStuff::readClient);
    connect(clientSocket, &QTcpSocket::disconnected, this, &ServerStuff::gotDisconnection);

    clients << clientSocket;

    QJsonObject doc;

    doc["type"] = "FromServer";
    doc["text"] = "connection established";

    sendToClient(clientSocket, doc);
}

void ServerStuff::slot_connectByNames(QString name1, QString name2){
    qDebug() << names;
    qDebug() << clients;
    pairs[name1] = clients[names.indexOf(name1)];
    pairs[name2] = clients[names.indexOf(name2)];

    QJsonObject doc;
    doc["type"] = "Dialog Entered";
    doc["name"] = name2;

    if (sendToClient(pairs[name1], doc) == -1){
        qDebug() << "Some error occured";
    }

    doc["name"] = name1;

    if (sendToClient(pairs[name2], doc) == -1){
        qDebug() << "Some error occured";
    }
    
}

bool ServerStuff::isConnected(QString name1, QString name2){
    return (pairs[name1] == clients[names.indexOf(name1)]) && (pairs[name2] == clients[names.indexOf(name2)]);
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

        // if (clientSocket->bytesAvailable() > 20000000){
        //         qDebug() << "flushing socket...";
        //         clientSocket->flush();
        //         continue;
        //     }



        if (clientSocket->bytesAvailable() < m_nNextBlockSize) { break; }
        // message;
        // qDebug() << clientSocket->bytesAvailable();
        // if (clientSocket->bytesAvailable() > )
         // while (clientSocket->bytesAvailable() > 0){
            qDebug() << "bytes to read: " << clientSocket->bytesAvailable() <<  m_nNextBlockSize << byteMessage.size();
            /*(if (clientSocket->waitForReadyRead()) */in >> byteMessage;
            // if (in.commitTransaction()){}

         // }
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
                    emit jsonReceived(jsonMessage.object(), clientSocket); // send the message to the central server
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
            m_nNextBlockSize = 0;
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

void ServerStuff::handleJson(QJsonObject message, QTcpSocket* clientSocket){
    // QVariantMap m = message.toVariantMap();
    // qDebug() << message["Login"].toString();
    // qDebug() << m.value("type");
    // emit gotNewMesssage("WHY");
    QJsonObject temp;

    // qDebug() << "GOT JSON" << sizeof(message);


    if (message["type"].toString() == "Login"){
        // qDebug() << message[""].toString();
        emit gotNewMesssage(message["name"].toString() + " connected");
        names << message["name"].toString();
        pairs[message["name"].toString()] = clientSocket;
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
                    if (sendToClient(pairs[message["dialogWith"].toString()], message) == -1){
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
    else if (message["type"].toString() == "getUsers"){
        temp["type"] = "getUsers";

        if (names.contains(message["name"].toString())){
            for (int i = 0; i < names.size(); i++){
                if (names[i] != message["name"].toString()) temp[QStringLiteral("user%1").arg(i)] = names[i];
            }
            sendToClient(pairs[message["name"].toString()], temp);
        }
    }
    else if (message["type"].toString() == "image"){
        if (names.contains(message["name"].toString()) && names.contains(message["dialogWith"].toString())){
            if (message["name"].toString() != message["dialogWith"].toString()){
                // emit gotNewMesssage(message["name"].toString() + " connected to " + message["dialogWith"].toString());
                //connect them
                if (isConnected(message["name"].toString(), message["dialogWith"].toString())){       
                    // qDebug() << names << names[i] << message["dialogWith"].toString();
                    // qDebug() << pairs;
                    qDebug() << "Image recieved";
                    // temp["type"] = "image";
                    // temp["img"] = message["img"];
                    emit gotNewMesssage(message["name"].toString() + " sending [" + message["text"].toString() + "] to " + message["dialogWith"].toString());
                    if (sendToClient(pairs[message["dialogWith"].toString()], message) == -1){
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
    else if (message["type"].toString() == "sound"){
        if (names.contains(message["name"].toString()) && names.contains(message["dialogWith"].toString())){
            if (message["name"].toString() != message["dialogWith"].toString()){
                // emit gotNewMesssage(message["name"].toString() + " connected to " + message["dialogWith"].toString());
                //connect them
                if (isConnected(message["name"].toString(), message["dialogWith"].toString())){       
                    // qDebug() << names << names[i] << message["dialogWith"].toString();
                    // qDebug() << pairs;
                    qDebug() << "Image recieved";
                    // temp["type"] = "image";
                    // temp["img"] = message["img"];
                    emit gotNewMesssage(message["name"].toString() + " sending [" + message["text"].toString() + "] to " + message["dialogWith"].toString());
                    if (sendToClient(pairs[message["dialogWith"].toString()], message) == -1){
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
    out << quint16(0) << QJsonDocument(doc).toJson(QJsonDocument::Compact);
    qDebug() << "message with size " << QJsonDocument(doc).toJson(QJsonDocument::Compact).size() << "was sent to client";

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    return socket->write(arrBlock);
}
