#ifndef CREATECONNECTIONCLIENT_H
#define CREATECONNECTIONCLIENT_H

#include <QObject>
#include <QTcpSocket>

class createConnectionCLient : public QObject
{
    Q_OBJECT
public:

    createConnectionCLient(const createConnectionCLient&) = delete;
    createConnectionCLient(createConnectionCLient&&) = delete;
    createConnectionCLient& operator=(const createConnectionCLient&) = delete;
    createConnectionCLient& operator=(createConnectionCLient&&) = delete;

    static QTcpSocket *get_instance(QString _host, quint16 _port);


private:
    createConnectionCLient();
    static createConnectionCLient *m_createClinet;
    static QTcpSocket *m_socket;
    QString m_host;
    quint16 m_port;

signals:
};

#endif // CREATECONNECTIONCLIENT_H
