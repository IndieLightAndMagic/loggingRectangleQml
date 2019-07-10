#include "loggingrectangletest.h"
#include <QVariant>
#include <QDebug>
#include <iostream>
#include <QQmlApplicationEngine>

void LoggingRectangle::install(const QQmlApplicationEngine& engine, const QString& objectName){

    auto theApplicationWindowRootObject = engine.rootObjects()[0];
    auto theApplicationWindowRootObjectChildren = theApplicationWindowRootObject->children();
    qDebug() << "RootName: " << theApplicationWindowRootObject->property("objectName").toString();


    for (const auto& theApplicationWindowRootObjectChild : theApplicationWindowRootObjectChildren){

        auto childrenName = theApplicationWindowRootObjectChild->property("objectName").toString();
        LoggingRectangle::pLoggingRectangleObject = theApplicationWindowRootObjectChild;

        if (childrenName == objectName){

            qInstallMessageHandler(LoggingRectangle::debugMessageHandler);
            break;

        }

    }
    if (LoggingRectangle::pLoggingRectangleObject){

        qDebug() << "Logging installed for " << objectName;
        qDebug() << LoggingRectangle::pLoggingRectangleObject;

    }

}

void LoggingRectangle::debugMessageHandler(QtMsgType msgType, const QMessageLogContext&, const QString& msg){

    auto ob = LoggingRectangle::pLoggingRectangleObject;
    auto msgLevel = QString("info");
        switch (msgType){
        case QtDebugMsg:
            msgLevel = "debug";
            break;
        case QtInfoMsg:
            msgLevel = "info";
            break;
        case QtCriticalMsg:
            msgLevel = "critical";
            break;
        case QtFatalMsg:
        default:
            msgLevel = "fatal";
            break;

        }
        auto ret = QVariant("");
        auto messageParameter = QVariant(msg);
        auto messageLevelParameter = QVariant(msgLevel);
        QMetaObject::invokeMethod(ob, "log", Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, messageParameter), Q_ARG(QVariant, messageLevelParameter));

}
QObject* LoggingRectangle::pLoggingRectangleObject{nullptr};

