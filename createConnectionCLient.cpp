#include "createConnectionCLient.h"

createConnectionCLient *createConnectionCLient::m_createClinet =nullptr;
QTcpSocket *createConnectionCLient::m_socket = nullptr;


QTcpSocket *createConnectionCLient::get_instance(QString _host , quint16 _port)
{

    if(m_socket == nullptr)
    {
        m_socket = new QTcpSocket;
        m_socket->connectToHost(_host , _port);
        return m_socket;
    }
    else{
        qDebug() << "it's open you can't open it again";
        return m_socket;
    }
}
