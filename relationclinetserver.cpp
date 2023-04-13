#include "relationclinetserver.h"
#include <string>
#include <iostream>

#define WIDTHQML  807
#define HEIGHTQML 534

#define PACKET_DATA_SIZE    8
#define PACKET_DATA_HEADER  2


RelationClinetServer::RelationClinetServer(QObject *parent)
    : QObject{parent},
      DATA_STATUS{DATASTATUS::PHASE_1}
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
    //    QVariantList _listQMLWrite;
    //    QVariantList _listQMLClean;

    double _valueQMLWrite;
    double _valueQMLClean;

    if(!m_list.isEmpty())
        _valueQMLWrite = m_list.takeFirst().toDouble();


    //    if(!m_pastList.isEmpty())
    //        _valueQMLClean = m_pastList.takeFirst().toDouble();

    //    if(m_pastList.length() == 970)
    //    {
    //        for(int i = 0 ; i < 6 ; i++)
    //        {
    //            _listQMLClean.append(m_pastList.takeFirst());
    //        }
    //    }

    //    if(m_list.size() > 8)
    //    {
    //        for(int i = 0 ; i < 6 ; i++)
    //        {
    //            _listQMLWrite.append(m_list.takeFirst());
    //        }
    //    }
    if(m_saveLifeButton)
    {
        _valueQMLWrite = rescaleNumbers(_valueQMLWrite, 0, HEIGHTQML, 0, 4);
        m_pastList.append(_valueQMLWrite);

    }

    sendGraphNumber(_valueQMLWrite);

    if(m_pastList.size() > 807)
        sendClearGraphNumber(_valueQMLClean);

}

double RelationClinetServer::rescaleNumbers(double _value, int RMin, int RMax, int RMinG, int RMaxG)
{
    //    for (int i = 0; i < _list.size(); i++) {
    //        _list.replace( i ,( (RMax - RMin) * ( (_list.value(i).toDouble())) / (RMaxG - RMinG)));
    //    }
    return ((RMax - RMin) * _value / (RMaxG - RMinG));

}

void RelationClinetServer::reciveServer()
{

    char _dataRecive[8] = {0};
    QByteArray _byteArray;

    static int8_t _indexResumData;
    int8_t     _checkNumberIndexRemove;

    _byteArray.append(m_socketClient->readAll());


    while (DATA_STATUS == DATASTATUS::PHASE_1 && _byteArray.size() >= PACKET_DATA_HEADER) {
        if (_byteArray[0] == 'H' && _byteArray[1] == 'i') {
            DATA_STATUS = DATASTATUS::PHASE_2;
            _byteArray.remove(0, PACKET_DATA_HEADER);
        }
        else {
            _byteArray.remove(0, PACKET_DATA_HEADER);
        }
    }

    if (DATA_STATUS == DATASTATUS::PHASE_2 && _byteArray.size() >= PACKET_DATA_SIZE) {
        memcpy(_dataRecive, _byteArray.constData(), PACKET_DATA_SIZE);
        _byteArray.remove(0, PACKET_DATA_SIZE);
        DATA_STATUS = DATASTATUS::PHASE_1;

        double* _dataConverted = reinterpret_cast<double*>(_dataRecive);
//        std::cout << "_dataConverted: " << *_dataConverted << std::endl;
        m_list.append(*_dataConverted);
        m_pastList.append(*_dataConverted);

        sendNumbers();
    }

}

void RelationClinetServer::sendStatusService(bool _status)
{

    m_saveLifeButton = _status;

    if(m_saveLifeButton == true)
    {
        m_socketClient->write("A");
    }
    else
    {
        m_socketClient->write("B");
    }

}
