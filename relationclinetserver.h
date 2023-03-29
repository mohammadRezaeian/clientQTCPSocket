#ifndef RELATIONCLINETSERVER_H
#define RELATIONCLINETSERVER_H

#include <QObject>
#include <QStringList>
#include <QDataStream>
#include <QVector>
#include <QByteArray>

#include "createConnectionCLient.h"

class RelationClinetServer : public QObject
{
    Q_OBJECT
public:
    explicit RelationClinetServer(QObject *parent = nullptr);
    QTcpSocket *m_socketClient;
signals:
    void sendGraphNumber(const QVariantList &_list);
    void exampleSignal();

private:
    void createConnection();
    QVector<double> m_saveDataServer;
private slots:
    void reciveServer();

};

#endif // RELATIONCLINETSERVER_H
