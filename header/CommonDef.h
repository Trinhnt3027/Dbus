#ifndef COMMONDEF_H
#define COMMONDEF_H

#include <QDebug>
#include <QThread>
#include <QCoreApplication>

#define LOG  qDebug() << LOG_TAG << "[" << QCoreApplication::applicationPid() << ":" << QThread::currentThreadId() << "] "

#define PATH_NAME   "/chat/broadcast"

#endif // COMMONDEF_H
