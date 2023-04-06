#include "ifaceqml.h"

IFaceQML::IFaceQML(QObject *parent)
    : QObject{parent}
{

}

void IFaceQML::inputReciveGraph(const QVariantList &_list)
{

    m_graphNumber = _list;
    emit getSizeList(m_graphNumber.length()-1);
    emit graphNumberChanged();
}


QVariantList IFaceQML::getGraphNumber()
{
    return m_graphNumber;
}


void IFaceQML::inputSetSatus(bool _status)
{
    setStatus(_status);
}

void IFaceQML::setStatus(bool &_status)
{
    m_status = _status;
    emit statusChanged();
    emit statusService(m_status);
}

void IFaceQML::recivedGraphNumber(QVariantList _list)
{
    if(!_list.size() == 0)
    {
        inputReciveGraph(_list);
    }
}


void IFaceQML::recivedClearGraphNumber(QVariantList _list)
{
    m_clearGraphNumber = _list;
    getSizeClear(m_clearGraphNumber.length()-1);
    emit clearGraphNumberChanged();
}

QVariantList IFaceQML::getClearGraphNumber()
{
    return m_clearGraphNumber;
}

bool IFaceQML::getStatus()
{
    return m_status;
}

