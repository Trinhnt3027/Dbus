#include <QApplication>
#include "ChatController.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ChatController chatController;
    chatController.initialize();

    return a.exec();
}
