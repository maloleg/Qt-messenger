#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QAudioFormat format;
    format.setChannelCount(1);
    format.setSampleRate(10000);
    format.setSampleSize(8);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::UnSignedInt);

    // QByteArray ba;
    // QBuffer bu(&ba);

    // buff->open("123.mp3");
    // QIODevice* buff = new QIODevice(this);
    // QIODevice* buff2 = new QIODevice(this);

    // QIODevice *buff2 = new QIODevice();

    buff2 = new QBuffer(this);

    buff2->open(QIODevice::ReadWrite);

    // 


    QAudioInput *audio = new QAudioInput(format, this);
    QAudioOutput *AudioOutput = new QAudioOutput(format, this);
    audio->setBufferSize(1024);
    AudioOutput->setBufferSize(1024);
    buff = audio->start();

    // buff3 = buff2;
    // buff2->open(QIODevice::ReadWrite);
    // buff->open(QIODevice::ReadWrite);

    // qDebug() << "how many" << buff2->write(buff->readAll()) << buff2->openMode();

    AudioOutput->start(buff2);

    // buff2->open(QIODevice::ReadWrite);    

    // AudioOutput->s;
    

    
    // audio->setNotifyInterval(50);

    // connect(audio, &QAudioInput::notify, this, &MainWindow::readSound);

    
    // qDebug() << buff->openMode() << buff2->openMode();

    // QThread::sleep (5);

    // audio->stop();

    // qDebug() << bu.readAll();

    // qDebug() << QCameraImageCapture::

    ui->pushButton_disconnect->setVisible(false);

    camera = new QCamera;
    viewfinder = new QCameraViewfinder;

    timer = new QTimer;

    imageCapture = new QCameraImageCapture(camera);

    timer->setInterval(50);

    connect(timer, &QTimer::timeout, this, &MainWindow::readSound);
    
    

    // qDebug() << camera->isCaptureModeSupported()

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
    else if (message["type"].toString() == "sound"){
        buff2->close();
        buff2->setData(QByteArray::fromBase64(message["data"].toString().toUtf8()));
        buff2->open(QIODevice::ReadOnly);
        qDebug() << "sound with size" << QByteArray::fromBase64(message["data"].toString().toUtf8()).size() << "recieved";
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
    // qDebug() << "playing";
    // QByteArray data = buff->readAll();
    // QIODevice* temp;
    // temp->write(data);
    
    // AudioOutput->start(temp);
    // AudioOutput->suspend();
    // qDebug() << "stopping";
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
    
    img.save(&bu, "JPEG", quality);
    // img.save("temp", "JPEG", 0);
    qDebug() << "size" << bu.data().size();

    // QByteArray da = qCompress(ba, 5);

    // qDebug() << "new" << bu.size() << da.size();
    // qDebug()
    QString imgBase64 = ba.toBase64();

    // qDebug() << imgBase64.size();
    // QString newSize = qCompress(imgBase64);
    // qDebug() << "new" << newSize.size();

    QJsonObject message;
    message["type"] = "image";
    message["name"] = ui->lineEdit->text();
    message["dialogWith"] = ui->lineEdit_2->text();
    message["img"] = imgBase64;


    // AudioOutput->suspend();

    // QByteArray temp = buff->readAll();
    // buff2->write(temp);
    // qDebug() << "size of sound" << temp.size();


    // AudioOutput->resume();

    // qDebug() << "playing";
    // QByteArray data = buff->readAll();
    // qDebug() << data << "\n-------------------------------------\n";
    // QBuffer* temp;
    // temp->write(data);
    
    // AudioOutput->start(temp);
    // AudioOutput->stop();
    // qDebug() << "stopping";
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
    // QAudioFormat format;
    // format.setChannelCount(1);
    // format.setSampleRate(10000);
    // format.setSampleSize(8);
    // format.setCodec("audio/pcm");
    // format.setByteOrder(QAudioFormat::LittleEndian);
    // format.setSampleType(QAudioFormat::UnSignedInt);

    // // QByteArray ba;
    // // QBuffer bu(&ba);

    // // buff->open("123.mp3");
    // // QIODevice* buff = new QIODevice(this);
    // // QIODevice* buff2 = new QIODevice(this);

    // // QIODevice *buff2 = new QIODevice();

    // buff2 = new QBuffer(this);

    // buff2->open(QIODevice::ReadWrite);

    // // 


    // QAudioInput *audio = new QAudioInput(format, this);
    // QAudioOutput *AudioOutput = new QAudioOutput(format, this);
    // audio->setBufferSize(1024);
    // AudioOutput->setBufferSize(1024);
    // buff = audio->start();

    // // buff3 = buff2;
    // // buff2->open(QIODevice::ReadWrite);
    // // buff->open(QIODevice::ReadWrite);

    // // qDebug() << "how many" << buff2->write(buff->readAll()) << buff2->openMode();

    // AudioOutput->start(buff2);

    // // buff2->open(QIODevice::ReadWrite);    

    // // AudioOutput->s;
    

    // connect(buff, &QIODevice::readyRead, this, &MainWindow::readSound);
    // // audio->setNotifyInterval(50);

    // // connect(audio, &QAudioInput::notify, this, &MainWindow::readSound);

    
    // // qDebug() << buff->openMode() << buff2->openMode();



    if (!timer->isActive()) {
        timer->start();
        // qDebug() << "!23";
        
        // QCameraViewfinderSettings viewfinderSettings;
        viewfinderSettings.setResolution(320, 240);

        camera->setViewfinder(viewfinder);
        camera->setViewfinderSettings(viewfinderSettings);
        // viewfinder->show();

        

        imageCapture->setCaptureDestination(QCameraImageCapture::CaptureToBuffer);

        camera->start();

    }
    else{
        timer->stop();
        camera->stop();
        AudioOutput->stop();
    } 
}

void MainWindow::on_pushButton_r1_clicked(){
    viewfinderSettings.setResolution(1280, 720);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_r2_clicked(){
    viewfinderSettings.setResolution(960, 540);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_r3_clicked(){
    viewfinderSettings.setResolution(640, 480);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_r4_clicked(){
    viewfinderSettings.setResolution(640, 360);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_r5_clicked(){
    viewfinderSettings.setResolution(320, 240);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_r6_clicked(){
    // Q
    viewfinderSettings.setResolution(160, 120);

    // camera->setViewfinder(viewfinder);
    camera->setViewfinderSettings(viewfinderSettings);
}

void MainWindow::on_pushButton_apply_clicked(){
    quality = ui->lineEdit_3->text().toInt();
}
void MainWindow::SendFrame(){
    // qDebug() << "snap!";
    if (imageCapture->isReadyForCapture()) {
        camera->searchAndLock();
       // cap->capture();
       
        imageCapture->capture("temp");
        camera->unlock();
    }
}

void MainWindow::readSound(){

    QByteArray temp = buff->readAll();
    qDebug() << "sound size" << temp.size();
   
    

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
 
    QJsonObject message;

    QString sound = temp.toBase64();
    message["type"] = "sound";
    message["name"] = ui->lineEdit->text();
    message["dialogWith"] = ui->lineEdit_2->text();
    message["data"] = sound;
    // message["name"] = ui->lineEdit->text();
    // message["dialogWith"] = ui->lineEdit_2->text();
    // message["friend"] = withWho;   

    // qDebug() << message;    
    
    out << quint16(0) << QJsonDocument(message).toJson(QJsonDocument::Compact);

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    client->tcpSocket->write(arrBlock);

    // buff2->close();
    // buff2->setData(temp);
    // buff2->open(QIODevice::ReadOnly);


    
    // qDebug() << "new sound size" << buff2->data().size();
    // buff2->write(temp);

    

    // AudioOutput->resume();
}