

ChatWindow::ChatWindow(QWidget *parent)
    : QWidget(parent)
    , m_chatClient(new ChatClient(this)) // create the chat client
    , m_chatModel(new QStandardItemModel(this)) // create the model to hold the messages
{
    // set up of the .ui file
    // ui->setupUi(this);
    connectButton = new QPushButton(tr("connect"), this);
    sendButton = new QPushButton(tr("send"), this);
    messageEdit = new QLineEdit(this);
    chatView = new QListView(this);

    // the model for the messages will have 1 column
    m_chatModel->insertColumn(0);
    // set the model as the data source vor the list view
    chatView->setModel(m_chatModel);
    // connect the signals from the chat client to the slots in this ui
    connect(m_chatClient, &ChatClient::connected, this, &ChatWindow::connectedToServer);
    connect(m_chatClient, &ChatClient::loggedIn, this, &ChatWindow::loggedIn);
    connect(m_chatClient, &ChatClient::loginError, this, &ChatWindow::loginFailed);
    connect(m_chatClient, &ChatClient::messageReceived, this, &ChatWindow::messageReceived);
    connect(m_chatClient, &ChatClient::disconnected, this, &ChatWindow::disconnectedFromServer);
    connect(m_chatClient, &ChatClient::error, this, &ChatWindow::error);
    connect(m_chatClient, &ChatClient::userJoined, this, &ChatWindow::userJoined);
    connect(m_chatClient, &ChatClient::userLeft, this, &ChatWindow::userLeft);
    // connect the connect button to a slot that will attempt the connection
    connect(connectButton, &QPushButton::clicked, this, &ChatWindow::attemptConnection);
    // connect the click of the "send" button and the press of the enter while typing to the slot that sends the message
    connect(sendButton, &QPushButton::clicked, this, &ChatWindow::sendMessage);
    connect(messageEdit, &QLineEdit::returnPressed, this, &ChatWindow::sendMessage);
}

ChatWindow::~ChatWindow(){
    // delete the elements created from the .ui file
    delete connectButton;
    delete sendtButton;
    delete chatView;
    delete messageEdit;
}

void ChatWindow::attemptConnection(){
    // We ask the user for the address of the server, we use 127.0.0.1 (aka localhost) as default
    const QString hostAddress = QInputDialog::getText(
        this
        , tr("Chose Server")
        , tr("Server Address")
        , QLineEdit::Normal
        , QStringLiteral("127.0.0.1")
    );
    if (hostAddress.isEmpty())
        return; // the user pressed cancel or typed nothing
    // disable the connect button to prevent the user clicking it again
    connectButton->setEnabled(false);
    // tell the client to connect to the host using the port 1967
    m_chatClient->connectToServer(QHostAddress(hostAddress), 1967);
}

void ChatWindow::connectedToServer(){
    // once we connected to the server we ask the user for what username they would like to use
    const QString newUsername = QInputDialog::getText(this, tr("Chose Username"), tr("Username"));
    if (newUsername.isEmpty()){
        // if the user clicked cancel or typed nothing, we just disconnect from the server
        return m_chatClient->disconnectFromHost();
    }
    // try to login with the given username
    attemptLogin(newUsername);
}

void ChatWindow::attemptLogin(const QString &userName){
    // use the client to attempt a log in with the given username
    m_chatClient->login(userName);
}

void ChatWindow::loggedIn()
{
    // once we successfully log in we enable the ui to display and send messages
    sendButton->setEnabled(true);
    messageEdit->setEnabled(true);
    chatView->setEnabled(true);
    // clear the user name record
    m_lastUserName.clear();
}


void ChatWindow::loginFailed(const QString &reason)
{
    // the server rejected the login attempt
    // display the reason for the rejection in a message box
    QMessageBox::critical(this, tr("Error"), reason);
    // allow the user to retry, execute the same slot as when just connected
    connectedToServer();
}


void ChatWindow::messageReceived(const QString &sender, const QString &text){
    // store the index of the new row to append to the model containing the messages
    int newRow = m_chatModel->rowCount();
    // we display a line containing the username only if it's different from the last username we displayed
    if (m_lastUserName != sender) {
        // store the last displayed username
        m_lastUserName = sender;
        // create a bold default font
        QFont boldFont;
        boldFont.setBold(true);
        // insert 2 row, one for the message and one for the username
        m_chatModel->insertRows(newRow, 2);
        // store the username in the model
        m_chatModel->setData(m_chatModel->index(newRow, 0), sender + ':');
        // set the alignment for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
        // set the for the username
        m_chatModel->setData(m_chatModel->index(newRow, 0), boldFont, Qt::FontRole);
        ++newRow;
    } else {
        // insert a row for the message
        m_chatModel->insertRow(newRow);
    }
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), text);
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignLeft | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // scroll the view to display the new message
    chatView->scrollToBottom();
}

void ChatWindow::sendMessage(){
    // we use the client to send the message that the user typed
    m_chatClient->sendMessage(messageEdit->text());
    // now we add the message to the list
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row for the message
    m_chatModel->insertRow(newRow);
    // store the message in the model
    m_chatModel->setData(m_chatModel->index(newRow, 0), messageEdit->text());
    // set the alignment for the message
    m_chatModel->setData(m_chatModel->index(newRow, 0), int(Qt::AlignRight | Qt::AlignVCenter), Qt::TextAlignmentRole);
    // clear the content of the message editor
    messageEdit->clear();
    // scroll the view to display the new message
    chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void ChatWindow::disconnectedFromServer()
{
    // if the client loses connection to the server
    // communicate the event to the user via a message box
    QMessageBox::warning(this, tr("Disconnected"), tr("The host terminated the connection"));
    // disable the ui to send and display messages
    sendButton->setEnabled(false);
    messageEdit->setEnabled(false);
    chatView->setEnabled(false);
    //nable the button to connect to the server again
    connectButton->setEnabled(true);
    // reset the last printed username
    m_lastUserName.clear();
}


void ChatWindow::userJoined(const QString &username){
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to communicate a user joined
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Joined the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::blue), Qt::ForegroundRole);
    // scroll the view to display the new message
    chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}
void ChatWindow::userLeft(const QString &username){
    // store the index of the new row to append to the model containing the messages
    const int newRow = m_chatModel->rowCount();
    // insert a row
    m_chatModel->insertRow(newRow);
    // store in the model the message to communicate a user left
    m_chatModel->setData(m_chatModel->index(newRow, 0), tr("%1 Left the Chat").arg(username));
    // set the alignment for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), Qt::AlignCenter, Qt::TextAlignmentRole);
    // set the color for the text
    m_chatModel->setData(m_chatModel->index(newRow, 0), QBrush(Qt::red), Qt::ForegroundRole);
    // scroll the view to display the new message
    chatView->scrollToBottom();
    // reset the last printed username
    m_lastUserName.clear();
}

void ChatWindow::error(QAbstractSocket::SocketError socketError){
    // show a message to the user that informs of what kind of error occurred
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
    case QAbstractSocket::ProxyConnectionClosedError:
        return; // handled by disconnectedFromServer
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The host refused the connection"));
        break;
    case QAbstractSocket::ProxyConnectionRefusedError:
        QMessageBox::critical(this, tr("Error"), tr("The proxy refused the connection"));
        break;
    case QAbstractSocket::ProxyNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the proxy"));
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::critical(this, tr("Error"), tr("Could not find the server"));
        break;
    case QAbstractSocket::SocketAccessError:
        QMessageBox::critical(this, tr("Error"), tr("You don't have permissions to execute this operation"));
        break;
    case QAbstractSocket::SocketResourceError:
        QMessageBox::critical(this, tr("Error"), tr("Too many connections opened"));
        break;
    case QAbstractSocket::SocketTimeoutError:
        QMessageBox::warning(this, tr("Error"), tr("Operation timed out"));
        return;
    case QAbstractSocket::ProxyConnectionTimeoutError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy timed out"));
        break;
    case QAbstractSocket::NetworkError:
        QMessageBox::critical(this, tr("Error"), tr("Unable to reach the network"));
        break;
    case QAbstractSocket::UnknownSocketError:
        QMessageBox::critical(this, tr("Error"), tr("An unknown error occurred"));
        break;
    case QAbstractSocket::UnsupportedSocketOperationError:
        QMessageBox::critical(this, tr("Error"), tr("Operation not supported"));
        break;
    case QAbstractSocket::ProxyAuthenticationRequiredError:
        QMessageBox::critical(this, tr("Error"), tr("Your proxy requires authentication"));
        break;
    case QAbstractSocket::ProxyProtocolError:
        QMessageBox::critical(this, tr("Error"), tr("Proxy communication failed"));
        break;
    case QAbstractSocket::TemporaryError:
    case QAbstractSocket::OperationError:
        QMessageBox::warning(this, tr("Error"), tr("Operation failed, please try again"));
        return;
    default:
        Q_UNREACHABLE();
    }
    // enable the button to connect to the server again
    connectButton->setEnabled(true);
    // disable the ui to send and display messages
    sendButton->setEnabled(false);
    messageEdit->setEnabled(false);
    chatView->setEnabled(false);
    // reset the last printed username
    m_lastUserName.clear();
}

