#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);

    }, Qt::QueuedConnection);
    engine.load(url);

    auto theApplicationWindowRootObject = engine.rootObjects()[0];
    auto theApplicationWindowRootObjectChildren = theApplicationWindowRootObject->children();
    qDebug() << "RootName: " << theApplicationWindowRootObject->property("objectName").toString();

    QObject* loggingRectangleObject{nullptr};

    for (const auto& theApplicationWindowRootObjectChild : theApplicationWindowRootObjectChildren){
        auto childrenName = theApplicationWindowRootObjectChild->property("objectName").toString();
        if (childrenName == "loggingRectangle"){
            loggingRectangleObject = theApplicationWindowRootObjectChild;
            qDebug() << "Found ====> " << loggingRectangleObject->property("objectName").toString();
            break;
        } else {
            qDebug() << "Not there yet.... " << childrenName;
        }
    }


    auto msg = QVariant("Hello from C++");
    auto info = QVariant("critical");
    auto ret = QVariant("");
    QMetaObject::invokeMethod(loggingRectangleObject, "log", Q_RETURN_ARG(QVariant, ret), Q_ARG(QVariant, msg), Q_ARG(QVariant, info));

    return app.exec();
}
