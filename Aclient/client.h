#pragma once

#include <QObject>
#include <QAbstractSocket>
#include <QString>
#include <QJsonObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QJsonDocument>
#include <QInputDialog>
#include <QStandardItemModel>
#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QLineEdit>
#include <QMessageBox>
#include <QHostAddress>


class ChatClient : public QObject{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
};

class ChatWindow : public QWidget{
    Q_OBJECT
    Q_DISABLE_COPY(ChatWindow)
public:
    ChatWindow(QWidget *parent = nullptr);
    ~ChatWindow();
private:
    // Ui::ChatWindow *ui;
    ChatClient *m_chatClient;
    QStandardItemModel *m_chatModel;
    QString m_lastUserName;

    QPushButton* connectButton;
    QPushButton* sendButton;
    QLineEdit* messageEdit;
    QListView* chatView;
private slots:
    void attemptConnection();
    void connectedToServer();
    void attemptLogin(const QString &userName);
    void loggedIn();
    void loginFailed(const QString &reason);
    void messageReceived(const QString &sender, const QString &text);
    void sendMessage();
    void disconnectedFromServer();
    void userJoined(const QString &username);
    void userLeft(const QString &username);
    void error(QAbstractSocket::SocketError socketError);
};