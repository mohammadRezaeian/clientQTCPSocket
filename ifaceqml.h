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

//    Q_PROPERTY(QVariantList m_graphNumber READ getGraphNumber NOTIFY graphNumberChanged)
//    Q_PROPERTY(QVariantList m_clearGraphNumber READ getClearGraphNumber  NOTIFY clearGraphNumberChanged)
    Q_PROPERTY(double m_graphNumber READ getGraphNumber NOTIFY graphNumberChanged)
    Q_PROPERTY(double m_clearGraphNumber READ getClearGraphNumber  NOTIFY clearGraphNumberChanged)

    Q_PROPERTY(bool m_status READ getStatus WRITE setStatus NOTIFY statusChanged)

    Q_INVOKABLE void inputReciveGraph(const double _value);


    Q_INVOKABLE void inputSetSatus(bool _status);

//    QVariantList getGraphNumber();
//    QVariantList getClearGraphNumber();
    double getGraphNumber();
    double getClearGraphNumber();

    bool getStatus();

private:
//    QVariantList m_graphNumber;
//    QVariantList m_clearGraphNumber;
    double m_graphNumber;
    double m_clearGraphNumber;
    bool m_status;

    void setStatus(bool &_status);
public slots:
    void recivedGraphNumber(double _value);
    void recivedClearGraphNumber(double _value);

signals:
    void  graphNumberChanged();
    void  testGraphNumber(double _value);
    void  clearGraphNumberChanged();
    void  statusChanged();
    void  getSizeList(int _size);
    void  getSizeClear(int _size);
    void  statusService(const bool &_status);
};
#endif // IFACEQML_H
