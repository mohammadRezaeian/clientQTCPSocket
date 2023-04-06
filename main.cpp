#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "ifaceqml.h"
#include "relationclinetserver.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    RelationClinetServer _relationClinetServer;
    IFaceQML _ifaceQML;

    QObject::connect(&_relationClinetServer, &RelationClinetServer::sendGraphNumber, &_ifaceQML , &IFaceQML::recivedGraphNumber );
    QObject::connect(&_relationClinetServer, &RelationClinetServer::sendClearGraphNumber, &_ifaceQML , &IFaceQML::recivedClearGraphNumber);

    QObject::connect(&_ifaceQML , &IFaceQML::statusService , &_relationClinetServer , &RelationClinetServer::sendStatusService);

    engine.rootContext()->setContextProperty("interfaceQML" ,  &_ifaceQML);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    engine.load(url);

    if(app.exec())
    {
        return app.exec();
    }
}
