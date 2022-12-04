#ifndef SERIAL_THREAD_H
#define SERIAL_THREAD_H


#include <QSerialPort>
#include <QObject>
#include <QByteArray>
#include <QList>

class serial_thread:public QObject
{
    Q_OBJECT

private:
    QSerialPort *serialPort;
    QByteArray m_readData;
    QList<int16_t> result_readData;
    //QList<QSerialPortInfo> list;

private slots:
    void handleReadyRead();

signals:
    void dataReadyRead();

public:
    serial_thread();
    void open_serial();
    void close_serial();
    QList<int16_t> getReadData();


};

#endif // SERIAL_THREAD_H
