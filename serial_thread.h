#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H


#include <QSerialPort>
#include <QObject>
#include <QByteArray>
#include <QList>
#include <QVector>

class serial_thread:public QObject
{
    Q_OBJECT

private:
    QSerialPort *serialPort;
    QByteArray m_readData;
    QVector<int16_t> result_readData;
    //QList<QSerialPortInfo> list;

private slots:
    void handleReadyRead();

signals:
    void dataReadyRead();

public:
    serial_thread();
    void open_serial();
    void close_serial();
    QVector<int16_t> getReadData();


};

#endif // SERIAL_THREAD_H
