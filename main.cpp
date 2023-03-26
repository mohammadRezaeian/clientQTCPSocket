#include <QCoreApplication>
#include "createConnectionCLient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <QVector>

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

        QByteArray _receivedData = _socketClient->readAll();
        QDataStream stream(&_receivedData, QIODevice::ReadOnly);
        QVector<double> _valueVector;
        stream >> _valueVector;

        for (int i = 0; i < _valueVector.size(); i++) {
            double _vectorValues = _valueVector[i];
            qDebug() << _vectorValues;
        }
//        _socketClient->close();
    }
    else
    {
        qDebug() << "Not connected!";
    }

    return a.exec();
}
