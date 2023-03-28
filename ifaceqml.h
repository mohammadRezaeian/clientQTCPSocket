#ifndef IFACEQML_H
#define IFACEQML_H

#include <QObject>
#include <QVariantList>

class IFaceQML : public QObject
{
    Q_OBJECT
public:
    explicit IFaceQML(QObject *parent = nullptr);

    Q_PROPERTY(QVariantList m_graphNumber READ getGraphNumber NOTIFY graphNumberChanged)
    Q_PROPERTY(bool m_status READ getStatus WRITE setStatus NOTIFY statusChanged)

    Q_INVOKABLE void reciveGraph(QVariantList _list);

    Q_INVOKABLE void status(bool _status);

    QVariantList getGraphNumber();
    bool getStatus();

private:
    QVariantList m_graphNumber;
    bool m_status;

    void setStatus(bool _status);

signals:
    void  graphNumberChanged();
    void  statusChanged();
};
#endif // IFACEQML_H
