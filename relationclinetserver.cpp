#include "relationclinetserver.h"
#define WIDTHQML  807
#define HEIGHTQML 540
RelationClinetServer::RelationClinetServer(QObject *parent)
    : QObject{parent}
{
    createConnection();
    connect(m_socketClient , &QTcpSocket::readyRead , this , &RelationClinetServer::reciveServer);

}

void RelationClinetServer::createConnection()
{
    m_socketClient = createConnectionCLient::get_instance("localhost" , 1234);
    if(m_socketClient->waitForConnected())
    {
        qDebug() << "connected to server";
    }
    else
    {
        qDebug() << "Please check your connection to internet";
    }
}

void RelationClinetServer::sendNumbers()
{
    QVariantList _listQMLWrite;
    QVariantList _listQMLClean;

    if(m_pastList.length() == 970)
    {
        for(int i = 0 ; i < 6 ; i++)
        {
            _listQMLClean.append(m_pastList.takeFirst());
        }
    }

    if(m_list.size() > 8)
    {
        for(int i = 0 ; i < 6 ; i++)
        {
            _listQMLWrite.append(m_list.takeFirst());
        }
    }

    if(m_saveLifeButton)
        rescaleNumbers(_listQMLWrite, 0, HEIGHTQML, 0, 8);

    sendGraphNumber(_listQMLWrite);
    sendClearGraphNumber(_listQMLClean);
}

void RelationClinetServer::rescaleNumbers(QVariantList &_list, int RMin, int RMax, int RMinG, int RMaxG)
{
    for (int i = 0; i < _list.size(); i++) {
        _list.replace( i , ( (RMax - RMin) * ( (_list.value(i).toDouble()) - RMinG) / (RMaxG - RMinG) + RMin) );
    }
}

void RelationClinetServer::reciveServer()
{
    double _templateValue;
    QByteArray _byteArray = m_socketClient->readAll();
    QDataStream _stream(&_byteArray , QIODevice::ReadOnly);
    _stream >> _templateValue;
    m_list.append(_templateValue);
    m_pastList.append(_templateValue);
            //    if(_counter == 807)
            //    {
            //        _counter = 0;
            //    }
            //    _counter++;
            //    if(m_saveLifeButton)
            //    {
            sendNumbers();
    //    }
    //    else{
    //        sendNumbers();
    //    }
}

void RelationClinetServer::sendStatusService(const bool &_status)
{
    m_saveLifeButton = _status;
    qDebug() << "m_saveLifeButton" << m_saveLifeButton;
    QByteArray _data;
    QDataStream _out(&_data , QIODevice::WriteOnly);
    _out << _status;
    m_socketClient->write(_data);
}
