#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
class ChatController;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(ChatController* controller, QWidget *parent = nullptr);
    ~MainWindow();

    void initialize();
    void updateMessageHistory(const QString& message);

private:
    void initConnection();
    void resetToDefaultWindow();

    void closeEvent(QCloseEvent *event) override;

private slots:
    void onSendBtnClicked();
    void onMessageTextChanged(const QString& message);

private:
    std::unique_ptr<Ui::MainWindow> mUiPtr;
    ChatController*                 mChatControllerPtr;
};
#endif // MAINWINDOW_H
