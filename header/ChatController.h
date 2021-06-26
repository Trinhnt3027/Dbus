#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>
#include <memory>
#include <broadcast_interface.h>

class MainWindow;
class NickName;

class ChatController : public QObject
{
    Q_OBJECT
public:
    explicit ChatController();
    ~ChatController();

    void initialize();

    void quitApplication();
    void joinChatRoom(const QString& nickName);
    void sendMessage(const QString& message);

private:
    void gotoLoginScreen();
    void deleteLoginScreen();
    void initDbus();
    void sendDbus(const QString& message);

signals:
    void messageReceived(const QString& message);

private slots:
    void onMessageReceived(const QString& message);

private:
    std::unique_ptr<MainWindow> mWindowPtr;
    std::unique_ptr<NickName>   mNickNamePtr;
    QString                     mNickname;
    local::ChatController*      mIface;
};

#endif // CHATCONTROLLER_H
