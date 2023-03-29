#ifndef IFACEQML_H
#define IFACEQML_H

#include <QObject>
#include <QVariantList>
#include <QDebug>

class IFaceQML : public QObject
{
    Q_OBJECT
public:
    explicit IFaceQML(QObject *parent = nullptr);

    Q_PROPERTY(QVariantList m_graphNumber READ getGraphNumber NOTIFY graphNumberChanged)
    Q_PROPERTY(bool m_status READ getStatus WRITE setStatus NOTIFY statusChanged)

    Q_INVOKABLE void inputReciveGraph(const QVariantList &_list);

    Q_INVOKABLE void inputSetSatus(bool _status);

    QVariantList getGraphNumber();
    bool getStatus();

private:
    QVariantList m_graphNumber;
    bool m_status;

    void setStatus(bool &_status);
public slots:
    void recivedGraphNumber(const QVariantList &_list);

signals:
    void  graphNumberChanged();
    void  statusChanged();
    void  getSizeList(int _size);
    void  statusService(const bool &_status);
};
#endif // IFACEQML_H
