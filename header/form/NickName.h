#ifndef NICKNAME_H
#define NICKNAME_H

#include <QDialog>

namespace Ui {
class NickName;
}
class ChatController;

class NickName : public QDialog
{
    Q_OBJECT

public:
    explicit NickName(ChatController* controller, QWidget *parent = nullptr);
    ~NickName();

private slots:
    void onBtnCancelClicked();
    void onBtnOkClick();
    void onNickNameTextChanged(const QString& nickName);

private:
    std::unique_ptr<Ui::NickName>   mUiPtr;
    ChatController*                 mChatControllerPtr;
};

#endif // NICKNAME_H
