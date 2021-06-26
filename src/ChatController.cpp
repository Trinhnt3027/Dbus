#include "ChatController.h"
#include "CommonDef.h"
#include "MainWindow.h"
#include "NickName.h"
#include "broadcast_adaptor.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "[ChatController]"

ChatController::ChatController()
    : mNickname("")
{

}

ChatController::~ChatController()
{
    LOG << "~ChatController";
}

void ChatController::initialize()
{
    LOG << "initialize";
    gotoLoginScreen();
}

void ChatController::quitApplication()
{
    sendDbus("left the chat");
}

void ChatController::joinChatRoom(const QString &nickName)
{
    LOG << "joinChatRoom nickName: " << nickName;
    mNickname = nickName;
    deleteLoginScreen();
    initDbus();

    mWindowPtr = std::make_unique<MainWindow>(this);
    mWindowPtr->initialize();
    mWindowPtr->show();

    sendDbus("join to the chat");
}

void ChatController::sendMessage(const QString &message)
{
    sendDbus(message);
}

void ChatController::gotoLoginScreen()
{
    LOG << "gotoLoginScreen";
    mNickNamePtr = std::make_unique<NickName>(this);
    connect(mNickNamePtr.get(), &NickName::destroyed, this, [&](){
        mNickNamePtr.release();
    });
    mNickNamePtr->show();
}

void ChatController::deleteLoginScreen()
{
    if (mNickNamePtr != nullptr) {
        mNickNamePtr->deleteLater();
    }
}

void ChatController::initDbus()
{
    LOG << "initDbus";
    QDBusConnection dbus = QDBusConnection::sessionBus();
    if (!dbus.registerObject(PATH_NAME, this)) {
        LOG << "registerObject ERROR";
    }

    new ChatControllerAdaptor(this);
    mIface = new local::ChatController(QString(), PATH_NAME, QDBusConnection::sessionBus(), this);

    dbus.connect(QString(), PATH_NAME, mIface->staticInterfaceName(), "messageReceived", this, SLOT(onMessageReceived(const QString &)));
}

void ChatController::sendDbus(const QString &message)
{
    LOG << "sendDbus message: " << message;
    QDBusMessage msg = QDBusMessage::createSignal(PATH_NAME, mIface->staticInterfaceName(), "messageReceived");
    QString data = QString("<%1> ").arg(mNickname).append(message);
    msg << data;
    QDBusConnection::sessionBus().send(msg);
}

void ChatController::onMessageReceived(const QString &message)
{
    LOG << "onMessageReceived: " << message;
    mWindowPtr->updateMessageHistory(message);
}
