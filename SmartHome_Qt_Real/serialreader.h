#ifndef SERIALREADER_H
#define SERIALREADER_H


#include <QObject>
#include <QtSerialPort/QSerialPort>

class SerialReader : public QObject {
    Q_OBJECT
public:
    explicit SerialReader(QObject *parent = nullptr);
    void start(const QString &portName);

signals:
    void newData(int temp, int light);

private slots:
    void handleReadyRead();

private:
    QSerialPort serial;
    QByteArray buffer;
};

#endif // SERIALREADER_H
