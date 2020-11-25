/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionchange_resolution;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_r2;
    QPushButton *pushButton_r6;
    QLabel *img_label;
    QPushButton *pushButton_sendPicture;
    QPushButton *pushButton_r1;
    QPushButton *pushButton_r4;
    QListWidget *listWidget;
    QPushButton *pushButton_r5;
    QPushButton *pushButton_r3;
    QGridLayout *gridLayout;
    QPushButton *pushButton_send;
    QLineEdit *lineEdit_message;
    QTextEdit *textEdit_log;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QPushButton *pushButton_dialogWith;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
    QLabel *label_status;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QPushButton *pushButton_apply;
    QPushButton *pushButtonGetUsers;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(755, 448);
        actionchange_resolution = new QAction(MainWindow);
        actionchange_resolution->setObjectName(QString::fromUtf8("actionchange_resolution"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_r2 = new QPushButton(centralWidget);
        pushButton_r2->setObjectName(QString::fromUtf8("pushButton_r2"));

        gridLayout_2->addWidget(pushButton_r2, 12, 1, 1, 1);

        pushButton_r6 = new QPushButton(centralWidget);
        pushButton_r6->setObjectName(QString::fromUtf8("pushButton_r6"));

        gridLayout_2->addWidget(pushButton_r6, 14, 1, 1, 1);

        img_label = new QLabel(centralWidget);
        img_label->setObjectName(QString::fromUtf8("img_label"));

        gridLayout_2->addWidget(img_label, 1, 2, 1, 1);

        pushButton_sendPicture = new QPushButton(centralWidget);
        pushButton_sendPicture->setObjectName(QString::fromUtf8("pushButton_sendPicture"));

        gridLayout_2->addWidget(pushButton_sendPicture, 0, 0, 1, 1);

        pushButton_r1 = new QPushButton(centralWidget);
        pushButton_r1->setObjectName(QString::fromUtf8("pushButton_r1"));

        gridLayout_2->addWidget(pushButton_r1, 12, 0, 1, 1);

        pushButton_r4 = new QPushButton(centralWidget);
        pushButton_r4->setObjectName(QString::fromUtf8("pushButton_r4"));

        gridLayout_2->addWidget(pushButton_r4, 13, 1, 1, 1);

        listWidget = new QListWidget(centralWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));

        gridLayout_2->addWidget(listWidget, 2, 1, 1, 1);

        pushButton_r5 = new QPushButton(centralWidget);
        pushButton_r5->setObjectName(QString::fromUtf8("pushButton_r5"));

        gridLayout_2->addWidget(pushButton_r5, 14, 0, 1, 1);

        pushButton_r3 = new QPushButton(centralWidget);
        pushButton_r3->setObjectName(QString::fromUtf8("pushButton_r3"));

        gridLayout_2->addWidget(pushButton_r3, 13, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton_send = new QPushButton(centralWidget);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setFlat(false);

        gridLayout->addWidget(pushButton_send, 6, 0, 1, 1);

        lineEdit_message = new QLineEdit(centralWidget);
        lineEdit_message->setObjectName(QString::fromUtf8("lineEdit_message"));

        gridLayout->addWidget(lineEdit_message, 6, 1, 1, 1);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QString::fromUtf8("textEdit_log"));

        gridLayout->addWidget(textEdit_log, 7, 1, 1, 1);

        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 8, 1, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 3, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 7, 0, 1, 1);

        pushButton_dialogWith = new QPushButton(centralWidget);
        pushButton_dialogWith->setObjectName(QString::fromUtf8("pushButton_dialogWith"));

        gridLayout->addWidget(pushButton_dialogWith, 5, 0, 1, 1);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 8, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_connect = new QPushButton(centralWidget);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        pushButton_connect->setFont(font);
        pushButton_connect->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        horizontalLayout_2->addWidget(pushButton_connect);

        pushButton_disconnect = new QPushButton(centralWidget);
        pushButton_disconnect->setObjectName(QString::fromUtf8("pushButton_disconnect"));
        pushButton_disconnect->setEnabled(true);
        pushButton_disconnect->setFont(font);
        pushButton_disconnect->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_2->addWidget(pushButton_disconnect);

        label_status = new QLabel(centralWidget);
        label_status->setObjectName(QString::fromUtf8("label_status"));
        label_status->setMaximumSize(QSize(9999, 16777215));
        label_status->setFont(font);
        label_status->setFrameShape(QFrame::Box);
        label_status->setFrameShadow(QFrame::Sunken);
        label_status->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_status);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 2);

        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 5, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 0, 1, 1);

        pushButton_apply = new QPushButton(centralWidget);
        pushButton_apply->setObjectName(QString::fromUtf8("pushButton_apply"));

        gridLayout->addWidget(pushButton_apply, 8, 2, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 0, 1, 1);

        pushButtonGetUsers = new QPushButton(centralWidget);
        pushButtonGetUsers->setObjectName(QString::fromUtf8("pushButtonGetUsers"));

        gridLayout_2->addWidget(pushButtonGetUsers, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pushButton_send->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Client", nullptr));
        actionchange_resolution->setText(QApplication::translate("MainWindow", "change resolution", nullptr));
        pushButton_r2->setText(QApplication::translate("MainWindow", "960x540", nullptr));
        pushButton_r6->setText(QApplication::translate("MainWindow", "160x120", nullptr));
        img_label->setText(QString());
        pushButton_sendPicture->setText(QApplication::translate("MainWindow", "SendPicture", nullptr));
        pushButton_r1->setText(QApplication::translate("MainWindow", "1280x720", nullptr));
        pushButton_r4->setText(QApplication::translate("MainWindow", "640x360", nullptr));
        pushButton_r5->setText(QApplication::translate("MainWindow", "320x240", nullptr));
        pushButton_r3->setText(QApplication::translate("MainWindow", "640x480", nullptr));
        pushButton_send->setText(QApplication::translate("MainWindow", "Send this:", nullptr));
        lineEdit_3->setText(QApplication::translate("MainWindow", "25", nullptr));
        lineEdit->setInputMask(QString());
        label_2->setText(QApplication::translate("MainWindow", "not selected", nullptr));
        pushButton_dialogWith->setText(QApplication::translate("MainWindow", "connect to:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "image quality (0-100)", nullptr));
        pushButton_connect->setText(QApplication::translate("MainWindow", "Connect to server", nullptr));
        pushButton_disconnect->setText(QApplication::translate("MainWindow", "Disconnect from server", nullptr));
        label_status->setText(QApplication::translate("MainWindow", "status", nullptr));
        lineEdit_2->setInputMask(QString());
        label->setText(QApplication::translate("MainWindow", "your name:", nullptr));
        pushButton_apply->setText(QApplication::translate("MainWindow", "apply", nullptr));
        pushButtonGetUsers->setText(QApplication::translate("MainWindow", "Get All users", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
