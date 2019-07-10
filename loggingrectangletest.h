#ifndef LOGGINGRECTANGLETEST_H
#define LOGGINGRECTANGLETEST_H

#include <QObject>
#include <QtGlobal>
#include <QQmlApplicationEngine>

struct LoggingRectangle
{
public:
    static void install(const QQmlApplicationEngine&, const QString& objectName = "loggingRectangle");
    static void debugMessageHandler(QtMsgType, const QMessageLogContext&, const QString&);
    static QObject* pLoggingRectangleObject;

};

#endif // LOGGINGRECTANGLETEST_H
