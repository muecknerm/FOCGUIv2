#include "serial_thread.h"
#include <QObject>
#include <QByteArray>
#include <QDebug>

serial_thread::serial_thread()
{
    serialPort = new QSerialPort();
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setPortName("COM9");

    for (quint8 i = 0; i < 25 ; i++)
    {
        result_readData.append(0);
    }

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

            for (quint8 i = 0; i < 25 ; i++)
            {
                 result_readData[i] = ((quint16) m_readData.at(i*2 + 2) << 8) | ((quint8) m_readData.at(i*2+1 + 2));
            }

            /*
            qDebug() << result_readData[0] << "[/]" << " | "
                     << result_readData[1] << "[°]" << " | "
                     << result_readData[18]<< "[A]" << " | "
                     << result_readData[19]<< "[A]";
                     */
        }
        m_readData.clear();

        emit dataReadyRead();
    }
}

QVector<int16_t> serial_thread::getReadData()
{
    return result_readData;
}

void serial_thread::setWriteData(quint16 id, quint16 value)
{
    QByteArray data;
    qint16 sendTmp = (qint16) value;
    data.resize(8);

    data[0] = 0x23;
    data[1] = 0x23;
    data[2] = id >> 8;
    data[3] = id >> 0;
    data[4] = sendTmp>>8;
    data[5] = sendTmp;
    data[6] = 0x01;
    data[7] = 0x01;

    serialPort->write(data);
    qDebug() << (quint8) data[4] <<  (quint8)data[5];
}

void dataReadyRead()
{

}

