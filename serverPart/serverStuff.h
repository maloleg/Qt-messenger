#ifndef SERVERSTUFF_H
#define SERVERSTUFF_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>

class ServerStuff : public QObject
{
    Q_OBJECT

public:
    ServerStuff(QObject *pwgt);
    QTcpServer *tcpServer;
    QList<QTcpSocket *> getClients();
    bool isConnected(QString name1, QString name2);

public slots:
    virtual void newConnection();
    void readClient();
    void gotDisconnection();
    qint64 sendToClient(QTcpSocket *socket, const QJsonObject message);
    void handleJson(QJsonObject message, QTcpSocket*);
    void slot_connectByNames(QString name1, QString name2);

signals:
    void gotNewMesssage(QString msg);
    void smbDisconnected();
    void jsonReceived(QJsonObject, QTcpSocket*);
    void connectByNames(QString name1, QString name2);

private:
    quint16 m_nNextBlockSize;
    QList<QTcpSocket*> clients;
    QList<QString> names;
    QMap<QString, QTcpSocket*> pairs;
};

#endif // SERVERSTUFF_H
