#include "NickName.h"
#include "ui_NickName.h"
#include "ChatController.h"
#include "CommonDef.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "[NickName]"

NickName::NickName(ChatController* controller, QWidget *parent)
    : QDialog(parent)
    , mChatControllerPtr(controller)
{
    mUiPtr = std::make_unique<Ui::NickName>();
    mUiPtr->setupUi(this);

    //Connection
    connect(mUiPtr->btnCancel          , &QPushButton::clicked      , this, &NickName::onBtnCancelClicked);
    connect(mUiPtr->btnOk              , &QPushButton::clicked      , this, &NickName::onBtnOkClick);
    connect(mUiPtr->nickNameText       , &QLineEdit::textChanged    , this, &NickName::onNickNameTextChanged);
}

NickName::~NickName()
{
    LOG << "~NickName";
}

void NickName::onBtnCancelClicked()
{
    LOG << "onBtnCancelClicked";
    reject();
//    mChatControllerPtr->quitApplication();
}

void NickName::onBtnOkClick()
{
    QString nickName = mUiPtr->nickNameText->text().trimmed();
    mChatControllerPtr->joinChatRoom(nickName);
    accept();
}

void NickName::onNickNameTextChanged(const QString &nickName)
{
    bool enableOkdBtn = !nickName.trimmed().isEmpty();
    mUiPtr->btnOk->setEnabled(enableOkdBtn);
    mUiPtr->btnOk->setDefault(enableOkdBtn);
    mUiPtr->btnCancel->setDefault(!enableOkdBtn);
}
