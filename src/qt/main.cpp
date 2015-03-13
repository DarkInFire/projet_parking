#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickItem>
#include "parking.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Parking parking;
    engine.rootContext()->setContextProperty("parking", &parking);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
