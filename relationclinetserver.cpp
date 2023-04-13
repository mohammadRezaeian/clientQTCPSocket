#include "relationclinetserver.h"
#include <string>
#include <iostream>

#define WIDTHQML  807
#define HEIGHTQML 534
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
    char       _checkValid[2];
    static char _dataRecive[8];
    QByteArray _byteArray;
    bool       _checkIsValid = false;
    bool       _saveCurrentData = false;
    bool       _dataCompleted = false;
    static int8_t _indexResumData;
    int8_t     _checkNumberIndexRemove;
    std::fill(_dataRecive ,_dataRecive + sizeof(_dataRecive) , '\0');

    _byteArray = m_socketClient->readAll();


    for(int _counterStateMachine = 10; _counterStateMachine <= _byteArray.size(); _counterStateMachine +=10)
    {

        if(_byteArray.at(0) == 'H' && _byteArray.at(1) == 'i')
        {
            _byteArray.remove(0 ,  1);
            _byteArray.remove(0 ,  1);
            m_statusMachin = STATEMACHIN_t::SM_DATANEWCOMING;
        }

        else
        {
            for(int i = 0; i <= _byteArray.size() ; i++)
            {
                if(!(_byteArray.at(0) == 'H' && _byteArray.at(1) == 'i'))
                {
                    _dataRecive[_indexResumData] = _byteArray.at(i);
                    _indexResumData++;
                    _checkNumberIndexRemove = i;
                }
                else
                {
                    for(int i = 0; i <= _checkNumberIndexRemove ; i++)
                    {
                        _byteArray.remove(i , _dataRecive[_checkNumberIndexRemove]);
                    }

                    double* _dataConverted = reinterpret_cast<double*>(_dataRecive);
                    std::cout << "_dataConverted" << *_dataConverted << std::endl;
                    m_list.append(*_dataConverted);

                    sendNumbers();
                    return;
                }
            }
        }

        if(m_statusMachin == STATEMACHIN_t::SM_DATANEWCOMING)
        {
            for(int i = 0; i < _byteArray.size() ; i++)
            {
                _dataRecive[i] = _byteArray.at(i);
                _indexResumData = i;
            }

            if(_dataRecive[7] == '\0')
            {
                m_statusMachin = STATEMACHIN_t::SM_DATARECIVEINCOMPLETE;
            }
            else
            {
                m_statusMachin = STATEMACHIN_t::SM_DATARECIVECOMPLETE;
            }
        }

        if(m_statusMachin == STATEMACHIN_t::SM_DATARECIVECOMPLETE)
        {
            for(int i = 0; i <= 7 ; i++)
            {
                _byteArray.remove(0 , 1);
            }

            double* _dataConverted = reinterpret_cast<double*>(_dataRecive);
            std::cout << "_dataConverted" << *_dataConverted << std::endl;
            m_list.append(*_dataConverted);

            sendNumbers();
        }
    };
}

void RelationClinetServer::sendStatusService(const bool &_status)
{
    m_saveLifeButton = _status;
    //    QByteArray _data;
    //    QDataStream _out(&_data , QIODevice::WriteOnly);
    //    _out << _status;
    //    m_socketClient->write(_data);

    if(m_saveLifeButton == true)
    {
        m_socketClient->write("start");
    }
    else
    {
        m_socketClient->write("stop");
    }

}
