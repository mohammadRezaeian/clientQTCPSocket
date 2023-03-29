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

void IFaceQML::setStatus(bool _status)
{
    m_status = _status;
    emit statusChanged();
}

void IFaceQML::recivedGraphNumber(const QVariantList &_list)
{
    inputReciveGraph(_list);
}

bool IFaceQML::getStatus()
{
    return m_status;
}

