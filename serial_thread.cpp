#include "serial_thread.h"
#include <QObject>
#include <QByteArray>
#include <QDebug>

serial_thread::serial_thread()
{
    serialPort = new QSerialPort();
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setPortName("COM9");

   // result_readData = new QList<int16_t>();

    result_readData.append(0);
    result_readData.append(0);
    result_readData.append(0);

    connect(serialPort, SIGNAL(readyRead()), this, SLOT(handleReadyRead()));
}

void serial_thread::open_serial()
{
    serialPort->open(QIODevice::ReadWrite);
}

void serial_thread::close_serial()
{
    serialPort->close();
}

void serial_thread::handleReadyRead()
{
    m_readData.append(serialPort->readAll());


    if (m_readData.size() >= 50)
    {
        if ((m_readData.at(0) == '#') && (m_readData.at(1) == '#') )
        {
            result_readData[0] = ((quint16) m_readData.at(36) << 8) | ((quint8) m_readData.at(37));
            result_readData[1] = ((quint16) m_readData.at(38) << 8) | ((quint8) m_readData.at(39));
            result_readData[2] = ((quint16) m_readData.at(40) << 8) | ((quint8) m_readData.at(41));

            qDebug() << result_readData[0];
        }
        m_readData.clear();

        emit dataReadyRead();
    }
}

QList<int16_t> serial_thread::getReadData()
{
    return result_readData;
}

void dataReadyRead()
{

}

