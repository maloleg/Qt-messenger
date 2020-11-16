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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QTextEdit *textEdit_log;
    QPushButton *pushButton_startServer;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_testConn;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_stopServer;
    QLineEdit *lineEdit;
    QPushButton *sendButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(402, 282);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(5, 5, 5, 5);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QString::fromUtf8("textEdit_log"));

        gridLayout->addWidget(textEdit_log, 2, 0, 1, 2);

        pushButton_startServer = new QPushButton(centralWidget);
        pushButton_startServer->setObjectName(QString::fromUtf8("pushButton_startServer"));
        pushButton_startServer->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        pushButton_startServer->setFont(font);
        pushButton_startServer->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));

        gridLayout->addWidget(pushButton_startServer, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_testConn = new QPushButton(centralWidget);
        pushButton_testConn->setObjectName(QString::fromUtf8("pushButton_testConn"));

        horizontalLayout->addWidget(pushButton_testConn);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 2);

        pushButton_stopServer = new QPushButton(centralWidget);
        pushButton_stopServer->setObjectName(QString::fromUtf8("pushButton_stopServer"));
        pushButton_stopServer->setEnabled(true);
        pushButton_stopServer->setFont(font);
        pushButton_stopServer->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        pushButton_stopServer->setCheckable(false);
        pushButton_stopServer->setChecked(false);
        pushButton_stopServer->setAutoDefault(false);
        pushButton_stopServer->setFlat(false);

        gridLayout->addWidget(pushButton_stopServer, 0, 1, 1, 1);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        gridLayout->addWidget(sendButton, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pushButton_stopServer->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Server", nullptr));
        pushButton_startServer->setText(QApplication::translate("MainWindow", "Start server", nullptr));
        pushButton_testConn->setText(QApplication::translate("MainWindow", "Test connection", nullptr));
        pushButton_stopServer->setText(QApplication::translate("MainWindow", "Stop server", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
