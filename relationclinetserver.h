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
    void sendGraphNumber(QVariantList _list);
    void sendClearGraphNumber(QVariantList _list);
    void exampleSignal();

private:
    void createConnection();
    void sendNumbers();
    void rescaleNumbers(QVariantList &_list , int RMin , int RMax , int RMinG , int RMaxG);
    QVariantList m_list;
    QVariantList m_pastList;
    bool m_saveLifeButton ;


private slots:
    void reciveServer();
public slots:
    void sendStatusService(const bool &_status);

};

#endif // RELATIONCLINETSERVER_H
