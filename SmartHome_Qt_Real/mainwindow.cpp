#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gpio.h"
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QRegularExpression>
#include "serialreader.h"

const int LED_RED = 17; //temp
const int LED_GREEN = 27;  //light
const int IR_SENSOR = 22;

const int LED_YELLOW = 23;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , serialReader(new SerialReader(this))
{
    ui->setupUi(this);

    setupGPIO(LED_RED, "out");
    setupGPIO(LED_GREEN, "out");
    setupGPIO(IR_SENSOR, "in");
    setupGPIO(LED_YELLOW, "out");

    serialReader->start("/dev/ttyACM0");

    connect(serialReader, &SerialReader::newData, this, &MainWindow::updateSensors);

    connect(ui->CheckBox, &QCheckBox::toggled, this, [=](bool checked){
        mockMotionValue = checked ? 1 : 0;
    });

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkMotion);
    timer->start(500);
}

void MainWindow::updateSensors(int temp, int light)
{
    qDebug() << "updateSensors called: TEMP =" << temp << ", LIGHT =" << light;

    ui->LM35_2->setValue(temp);
    ui->LDR_2->setValue(light);
    ui->LM35value->setText(QString::number(temp));
    ui->LDRvalue->setText(QString::number(light));

    if (temp > 30) {
        qDebug() << "Red LED ON";
        ui->red->setPixmap(QPixmap(":/Icons/redon.png").scaled(64, 64));
        writeGPIO(LED_RED, 1);
    } else {
        qDebug() << "Red LED OFF";
        ui->red->setPixmap(QPixmap(":/Icons/redoff.jpeg").scaled(64, 64));
        writeGPIO(LED_RED, 0);
    }

    if (light >= 300) {
        qDebug() << "Sun ON";
        ui->sun->setPixmap(QPixmap(":/Icons/lighton.png").scaled(300, 100, Qt::KeepAspectRatio));
    } else {
        qDebug() << "Sun OFF";
        ui->sun->setPixmap(QPixmap(":/Icons/lightoff.png").scaled(300, 100, Qt::KeepAspectRatio));
    }
}

/*void MainWindow::checkMotion()
{
    qDebug() << "checkMotion triggered";

    int motion = readGPIO(IR_SENSOR);
    int light = ui->LDR_2->value();

    qDebug() << "Motion =" << motion << ", Light =" << light;

    if (motion == 0) { // في حركة
        qDebug() << "Motion detected";
        ui->motion->setPixmap(QPixmap(":/Icons/motion.png").scaled(100, 100, Qt::KeepAspectRatio));
        ui->yellow->setPixmap(QPixmap(":/Icons/yellowon.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        writeGPIO(LED_YELLOW, 1);

        if (light < 300) {
            qDebug() << "Green LED ON";
            writeGPIO(LED_GREEN, 1);
            ui->green->setPixmap(QPixmap(":/Icons/greenon.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        } else {
            qDebug() << "Green LED OFF (light high)";
            writeGPIO(LED_GREEN, 0);
            ui->green->setPixmap(QPixmap(":/Icons/greenoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        }
    } else {
        qDebug() << "No motion";
        ui->yellow->setPixmap(QPixmap(":/Icons/yellowoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        writeGPIO(LED_YELLOW, 0);
        writeGPIO(LED_GREEN, 0);
        ui->green->setPixmap(QPixmap(":/Icons/greenoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
    }
}*/

void MainWindow::checkMotion()
{
    int motion = mockMotionValue;
    int light = ui->LDR_2->value();

    if (motion == 1) {
        ui->motion->setVisible(true);
        ui->yellow->setPixmap(QPixmap(":/Icons/yellowon.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        ui->motion->setPixmap(QPixmap(":/Icons/motion.png").scaled(64, 64, Qt::KeepAspectRatio));

        writeGPIO(LED_YELLOW, 1);

        if (light < 300) {
            writeGPIO(LED_GREEN, 1);
            ui->green->setPixmap(QPixmap(":/Icons/greenon.jpeg").scaled(70, 70, Qt::KeepAspectRatio));
        } else {
            writeGPIO(LED_GREEN, 0);
            ui->green->setPixmap(QPixmap(":/Icons/greenoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        }
    } else {
        ui->yellow->setPixmap(QPixmap(":/Icons/yellowoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        writeGPIO(LED_YELLOW, 0);
        writeGPIO(LED_GREEN, 0);
        ui->green->setPixmap(QPixmap(":/Icons/greenoff.jpeg").scaled(64, 64, Qt::KeepAspectRatio));
        ui->motion->setVisible(false);

    }
}



MainWindow::~MainWindow() { delete ui; }
