#include "client.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    ChatWindow chatWin;
    chatWin.setFixedSize(500, 500);
    chatWin.show();
    return a.exec();
}