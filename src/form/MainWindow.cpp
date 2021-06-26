#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "CommonDef.h"
#include "ChatController.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "[MainWindow]"

MainWindow::MainWindow(ChatController* controller, QWidget *parent)
    : QMainWindow(parent)
    , mChatControllerPtr(controller)
{
    mUiPtr = std::make_unique<Ui::MainWindow>();
    mUiPtr->setupUi(this);
}

MainWindow::~MainWindow()
{
    LOG << "~MainWindow";
}

void MainWindow::initialize()
{
    LOG << "initialize";
    initConnection();
}

void MainWindow::updateMessageHistory(const QString &message)
{
    mUiPtr->chatHistory->append(message);
}

void MainWindow::initConnection()
{
    LOG << "initConnection";
    connect(mUiPtr->sendBtn       , &QPushButton::clicked       , this, &MainWindow::onSendBtnClicked);
    connect(mUiPtr->messageText   , &QLineEdit::returnPressed   , this, &MainWindow::onSendBtnClicked);
    connect(mUiPtr->messageText   , &QLineEdit::textChanged     , this, &MainWindow::onMessageTextChanged);
}

void MainWindow::resetToDefaultWindow()
{
    mUiPtr->messageText->clear();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    mChatControllerPtr->quitApplication();
}

void MainWindow::onSendBtnClicked()
{
    QString message = mUiPtr->messageText->text();
    if (!message.trimmed().isEmpty()) {
        mChatControllerPtr->sendMessage(message);
        resetToDefaultWindow();
    }
}

void MainWindow::onMessageTextChanged(const QString &message)
{
    bool enabledBtn = !message.trimmed().isEmpty();
    mUiPtr->sendBtn->setEnabled(enabledBtn);
    mUiPtr->sendBtn->setDefault(enabledBtn);
    mUiPtr->sendBtn->setAutoDefault(enabledBtn);
    if (!enabledBtn) {
        mUiPtr->messageText->setFocus();
    }
}
