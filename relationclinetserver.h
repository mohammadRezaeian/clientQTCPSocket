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
//    void sendGraphNumber(QVariantList _list);
//    void sendClearGraphNumber(QVariantList _list);
    void sendGraphNumber(double _value);
    void sendClearGraphNumber(double _value);
    void exampleSignal();

private:
    void createConnection();
    void sendNumbers();
    double rescaleNumbers   (double _value , int RMin , int RMax , int RMinG , int RMaxG);
    QVariantList m_list;
    QVariantList m_pastList;
    bool m_saveLifeButton ;

    enum STATEMACHIN_t{
        SM_DATANEWCOMING,
        SM_DATARECIVECOMPLETE,
        SM_DATARECIVEINCOMPLETE
    };
    STATEMACHIN_t m_statusMachin;

    enum DATASTATUS {
        PHASE_1,
        PHASE_2
    } DATA_STATUS;

private slots:
    void reciveServer();
public slots:
    void sendStatusService(bool _status);

};

#endif // RELATIONCLINETSERVER_H
