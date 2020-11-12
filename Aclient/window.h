#pragma once

#include <QStandardItemModel>
#include <QWidget>
#include <QPushButton>
#include <QListView>
#include <QLineEdit>
#include <QAbstractSocket>
#include <QString>


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