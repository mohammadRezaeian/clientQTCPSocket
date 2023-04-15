#include "ifaceqml.h"

IFaceQML::IFaceQML(QObject *parent)
    : QObject{parent}
{

}

void IFaceQML::inputReciveGraph(const double _value)
{
    m_graphNumber = _value;
    emit testGraphNumber(m_graphNumber);
}


double IFaceQML::getGraphNumber()
{
    return m_graphNumber;
}


void IFaceQML::inputSetSatus(bool _status)
{
    setStatus(_status);
}

void IFaceQML::setStatus(bool _status)
{
    m_status = _status;
    emit statusChanged();
    emit statusService(_status);
}

void IFaceQML::recivedGraphNumber(double _value)
{
    inputReciveGraph(_value);

}


void IFaceQML::recivedClearGraphNumber(double _value)
{
    m_clearGraphNumber = _value;
//    getSizeClear(m_clearGraphNumber.length()-1);
    emit clearGraphNumberChanged();
}

double IFaceQML::getClearGraphNumber()
{
    return m_clearGraphNumber;
}

bool IFaceQML::getStatus()
{
    return m_status;
}

