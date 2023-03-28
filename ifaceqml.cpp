#include "ifaceqml.h"

IFaceQML::IFaceQML(QObject *parent)
    : QObject{parent}
{

}

void IFaceQML::reciveGraph(QVariantList _list)
{
    m_graphNumber = _list;
    emit graphNumberChanged();
}

QVariantList IFaceQML::getGraphNumber()
{
    return m_graphNumber;
}

void IFaceQML::status(bool _status)
{
    setStatus(_status);
}

void IFaceQML::setStatus(bool _status)
{
    m_status = _status;
    emit statusChanged();
}

bool IFaceQML::getStatus()
{
    return m_status;
}

