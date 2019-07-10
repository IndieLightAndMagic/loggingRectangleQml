#ifndef LOGGINGRECTANGLETEST_H
#define LOGGINGRECTANGLETEST_H

#include <QObject>
#include <QtGlobal>
#include <QQuickItem>
#include <QQuickView>
#include <QQmlApplicationEngine>

#include <QQmlApplicationEngine>

struct LoggingRectangle
{
    LoggingRectangle() = delete;
    static void install(const QQuickView& view, const QString& objectName = "loggingRectangle");
    static void install(const QQmlApplicationEngine&, const QString& objectName = "loggingRectangle");
    static void debugMessageHandler(QtMsgType, const QMessageLogContext&, const QString&);
    static QObject* pLoggingRectangleObject;

};

#endif // LOGGINGRECTANGLETEST_H
