#include "relationclinetserver.h"

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

void RelationClinetServer::reciveServer()
{
    QByteArray _byteArray = m_socketClient->readAll();
    QDataStream _stream(&_byteArray , QIODevice::ReadOnly);
    _stream >> m_saveDataServer;

    QVariantList _list;
    foreach (auto &_qVariant, m_saveDataServer)
    {
       _list.append(_qVariant);
    }

    emit sendGraphNumber(_list);
}

void RelationClinetServer::sendStatusService(const bool &_status)
{
    qDebug() << "status is" << _status;
    QByteArray _data;
    QDataStream _out(&_data , QIODevice::WriteOnly);
    _out << _status;

    m_socketClient->write(_data);
}
