#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QRegularExpression>
#include "serialreader.h"

SerialReader::SerialReader(QObject *parent) : QObject(parent) {}

void SerialReader::start(const QString &portName) {
    serial.setPortName(portName);
    serial.setBaudRate(QSerialPort::Baud115200);
    if (serial.open(QIODevice::ReadOnly)) {
        connect(&serial, &QSerialPort::readyRead, this, &SerialReader::handleReadyRead);
        qDebug() << "Serial port opened on" << portName;
    } else {
        qDebug() << "Failed to open serial port";
    }
}

void SerialReader::handleReadyRead() {
    buffer.append(serial.readAll());
    if (buffer.contains('\n')) {
        QList<QByteArray> lines = buffer.split('\n');
        for (int i = 0; i < lines.size() - 1; ++i) {
            QString data = lines[i];
            if (data.contains("TEMP:") && data.contains("LIGHT:")) {
                QStringList parts = data.split(QRegularExpression("[ :]+"), Qt::SkipEmptyParts);
                int temp = 0, light = 0;
                for (int j = 0; j < parts.size(); ++j) {
                    if (parts[j] == "TEMP" && j+1 < parts.size()) temp = parts[j+1].toInt();
                    if (parts[j] == "LIGHT" && j+1 < parts.size()) light = parts[j+1].toInt();
                }
                emit newData(temp, light);
            }
        }
        buffer.clear();
    }
}
