#include "ifaceqml.h"

IFaceQML::IFaceQML(QObject *parent)
    : QObject{parent}
{

}

void IFaceQML::inputReciveGraph(QVariantList _list)
{
    m_graphNumber = _list;
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
    qDebug() << _list;
}

bool IFaceQML::getStatus()
{
    return m_status;
}

