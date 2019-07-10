#include "loggingrectangletest.h"
#include <QVariant>
#include <QDebug>
#include <iostream>

static QObject* getObjectPtr(QObjectList pobjects, const QString& objectNames){

    if (pobjects.isEmpty()) return nullptr;
    auto objectNamesList = objectNames.split(".");
    auto objectName = objectNamesList[0];
    auto namesLeft = objectNamesList.count();
    if (!namesLeft) return nullptr;


    for (auto pobject : pobjects){
        auto pobjectname = pobject->property("objectName").toString();
        if (pobjectname == objectName){

            objectNamesList.removeAt(0);
            if (namesLeft == 1) return pobject;
            return getObjectPtr(pobject->children(), objectNamesList.join("."));
        }
    }
    return nullptr;

}
void install(QObject* pObject){

    LoggingRectangle::pLoggingRectangleObject = pObject;
    if (LoggingRectangle::pLoggingRectangleObject){
        qInstallMessageHandler(LoggingRectangle::debugMessageHandler);
        qDebug() << "Logging installed for " << pObject->property("objectName");
        qDebug() << LoggingRectangle::pLoggingRectangleObject;

    } else qInstallMessageHandler(0);

}
 void LoggingRectangle::install(const QQuickView& view, const QString& objectName){

    auto pitem = view.rootObject();
    auto pitemname = pitem->property("objectName");
    auto pobjects = pitem->children();

    ::install(getObjectPtr(pobjects, objectName));

}

void LoggingRectangle::install(const QQmlApplicationEngine& engine, const QString& objectName){

    auto pobjects = engine.rootObjects()[0]->children();
    ::install(getObjectPtr(pobjects, objectName));
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

