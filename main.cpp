#include <QCoreApplication>
#include "createConnectionCLient.h"
#include <QTcpSocket>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTcpSocket *_socketClient = createConnectionCLient::get_instance("localhost" , 1234);

    if(_socketClient->waitForConnected(3000))
    {
        qDebug() << "Connected!";

        // send
        _socketClient->write("hello server");
        _socketClient->flush();
        _socketClient->waitForBytesWritten(1000);
        _socketClient->waitForReadyRead(3000);

        qDebug() << "Reading: " << _socketClient->bytesAvailable();

        qDebug() << _socketClient->readAll();

//        _socketClient->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }

    return a.exec();
}
