#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <QRandomGenerator>
#include <QPixmap>
#include <QPainter>
#include <QNetworkRequest>
#include <QDebug>
#include <QStyleOption>
#include <QApplication>

//////////////////////
// MJPEGReceiver
//////////////////////
MJPEGReceiver::MJPEGReceiver(const QUrl &url, QObject *parent)
    : QObject(parent), m_url(url), m_reply(nullptr)
{
}

MJPEGReceiver::~MJPEGReceiver(){
    stop();
}

void MJPEGReceiver::start(){
    stop();
    QNetworkRequest req(m_url);
    req.setRawHeader("User-Agent", "QtMjpegReceiver");
    m_reply = m_nam.get(req);
    connect(m_reply, &QNetworkReply::readyRead, this, &MJPEGReceiver::readyRead);
    connect(m_reply, &QNetworkReply::finished, this, &MJPEGReceiver::finished);
}

void MJPEGReceiver::stop(){
    if(m_reply){
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = nullptr;
    }
}

void MJPEGReceiver::finished(){
    // closed or error
    if(m_reply->error() != QNetworkReply::NoError){
        emit errorOccured(m_reply->errorString());
    }
    stop();
}

void MJPEGReceiver::readyRead(){
    if(!m_reply) return;
    m_buffer.append(m_reply->readAll());
    // naive parse: find JPEG SOI/EOI markers
    int start = m_buffer.indexOf("\xFF\xD8");
    int end = m_buffer.indexOf("\xFF\xD9", start);
    if(start >=0 && end > start){
        QByteArray jpg = m_buffer.mid(start, end - start + 2);
        m_buffer = m_buffer.mid(end+2);
        QImage img;
        img.loadFromData(jpg, "JPG");
        if(!img.isNull()){
            m_frame = img;
            emit frameReady(img);
        }
    }
}

QImage MJPEGReceiver::latestFrame() const {
    return m_frame;
}

//////////////////////
// MainWindow
//////////////////////

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    m_tempChart(new QChart()),
    m_tempSeries(new QLineSeries()),
    m_tempChartView(new QChartView(m_tempChart)),
    m_ldrChart(new QChart()),
    m_ldrSeries(new QLineSeries()),
    m_ldrChartView(new QChartView(m_ldrChart))
{
    setupUi();
    setupCharts();
    applyDarkStyle();

    // timer every second
    connect(&m_timer, &QTimer::timeout, this, &MainWindow::onTick);
    m_timer.start(1000);

    // Optional: start MJPEG if you have a stream at this address:
    // change to your MJPEG URL, or leave commented to use placeholder.
    QUrl mjpegUrl("http://127.0.0.1:8081/?action=stream"); // try mjpg-streamer
    m_mjpeg = new MJPEGReceiver(mjpegUrl, this);
    connect(m_mjpeg, &MJPEGReceiver::frameReady, this, &MainWindow::onMjpegFrame);
    connect(m_mjpeg, &MJPEGReceiver::errorOccured, [](const QString &err){ qDebug() << "MJPEG error:" << err; });
    // start only if the stream exists: you may comment this out if no stream
    m_mjpeg->start();
}

MainWindow::~MainWindow(){
    if(m_mjpeg) m_mjpeg->stop();
}

void MainWindow::setupUi(){
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLay = new QVBoxLayout(central);
    mainLay->setContentsMargins(12,12,12,12);
    mainLay->setSpacing(10);

    // Top status
    QHBoxLayout *topLay = new QHBoxLayout;
    m_clockLabel = new QLabel("—", this);
    m_clockLabel->setStyleSheet("font-size:20px; color:#00FFFF;"); // cyan
    m_statusMotion = new QLabel("Motion: No", this);
    m_statusMotion->setStyleSheet("font-size:18px; color:#FF6B6B;");
    topLay->addWidget(m_clockLabel);
    topLay->addStretch();
    topLay->addWidget(m_statusMotion);
    mainLay->addLayout(topLay);

    // Row 1: three cards horizontally
    QHBoxLayout *row1 = new QHBoxLayout;
    // Temperature card (left)
    QWidget *tempCard = new QWidget(this);
    tempCard->setStyleSheet("background:#1b1b1b;border-radius:10px;padding:10px;");
    QVBoxLayout *tcL = new QVBoxLayout(tempCard);
    m_tempBig = new QLabel("Temp: -- °C", this);
    m_tempBig->setAlignment(Qt::AlignCenter);
    m_tempBig->setStyleSheet("font-size:28px;color:#BEE3F8;");
    tcL->addWidget(m_tempBig);
    tcL->addWidget(m_tempChartView);
    row1->addWidget(tempCard, 1);

    // LDR card (middle)
    QWidget *ldrCard = new QWidget(this);
    ldrCard->setStyleSheet("background:#1b1b1b;border-radius:10px;padding:10px;");
    QVBoxLayout *lcL = new QVBoxLayout(ldrCard);
    m_ldrBig = new QLabel("LDR: --", this);
    m_ldrBig->setAlignment(Qt::AlignCenter);
    m_ldrBig->setStyleSheet("font-size:28px;color:#FFE680;");
    lcL->addWidget(m_ldrBig);
    lcL->addWidget(m_ldrChartView);
    row1->addWidget(ldrCard, 1);

    // Motion card (right)
    QWidget *motionCard = new QWidget(this);
    motionCard->setStyleSheet("background:#1b1b1b;border-radius:10px;padding:10px;");
    QVBoxLayout *mcL = new QVBoxLayout(motionCard);
    QLabel *motionTitle = new QLabel("Motion Sensor", this);
    motionTitle->setAlignment(Qt::AlignCenter);
    motionTitle->setStyleSheet("font-size:20px;color:#FF7777;");
    mcL->addWidget(motionTitle);
    QLabel *motionIcon = new QLabel(this);
    motionIcon->setPixmap(QPixmap(64,64));
    mcL->addWidget(motionIcon,0,Qt::AlignCenter);
    row1->addWidget(motionCard, 1);

    mainLay->addLayout(row1, 2);

    // Row 2: Camera on left + LED panel on right
    QHBoxLayout *row2 = new QHBoxLayout;

    // Camera frame
    QWidget *camCard = new QWidget(this);
    camCard->setStyleSheet("background:#1b1b1b;border-radius:10px;padding:10px;");
    QVBoxLayout *camL = new QVBoxLayout(camCard);
    QLabel *camTitle = new QLabel("Camera", this);
    camTitle->setStyleSheet("font-size:18px;color:#BEE3F8;");
    camL->addWidget(camTitle);
    m_cameraLabel = new QLabel(this);
    m_cameraLabel->setFixedSize(640,360);
    m_cameraLabel->setStyleSheet("background:#000;border-radius:6px;");
    m_cameraLabel->setAlignment(Qt::AlignCenter);
    // placeholder image
    QPixmap placeholder(m_cameraLabel->size());
    placeholder.fill(Qt::black);
    m_cameraLabel->setPixmap(placeholder);
    camL->addWidget(m_cameraLabel);
    row2->addWidget(camCard, 2);

    // LED panel
    QWidget *ledCard = new QWidget(this);
    ledCard->setStyleSheet("background:#1b1b1b;border-radius:10px;padding:10px;");
    QVBoxLayout *ledL = new QVBoxLayout(ledCard);
    QLabel *ledTitle = new QLabel("LED Controls", this);
    ledTitle->setStyleSheet("font-size:18px;color:#A9FFB1;");
    ledL->addWidget(ledTitle);
    for(int i=0;i<4;i++){
        m_ledButtons[i] = new QPushButton(QString("LED %1 OFF").arg(i+1), this);
        m_ledButtons[i]->setCheckable(true);
        m_ledButtons[i]->setMinimumHeight(48);
        ledL->addWidget(m_ledButtons[i]);
        connect(m_ledButtons[i], &QPushButton::clicked, this, &MainWindow::onLedButton);
    }
    ledL->addStretch();
    row2->addWidget(ledCard, 1);

    mainLay->addLayout(row2, 2);
}

void MainWindow::setupCharts(){
    // Temperature chart
    m_tempChart->addSeries(m_tempSeries);
    QValueAxis *axX = new QValueAxis();
    axX->setRange(0,60);
    axX->setVisible(false);
    QValueAxis *axY = new QValueAxis();
    axY->setRange(0,50);
    m_tempChart->addAxis(axX, Qt::AlignBottom);
    m_tempSeries->attachAxis(axX);
    m_tempChart->addAxis(axY, Qt::AlignLeft);
    m_tempSeries->attachAxis(axY);
    m_tempChartView->setRenderHint(QPainter::Antialiasing);

    // LDR chart
    m_ldrChart->addSeries(m_ldrSeries);
    QValueAxis *lx = new QValueAxis();
    lx->setRange(0,60);
    lx->setVisible(false);
    QValueAxis *ly = new QValueAxis();
    ly->setRange(0,1023);
    m_ldrChart->addAxis(lx, Qt::AlignBottom);
    m_ldrSeries->attachAxis(lx);
    m_ldrChart->addAxis(ly, Qt::AlignLeft);
    m_ldrSeries->attachAxis(ly);
    m_ldrChartView->setRenderHint(QPainter::Antialiasing);
}

void MainWindow::applyDarkStyle(){
    QString s = R"(
      QWidget { background: #121212; color: #ffffff; }
      QChartView { background: transparent; }
      QPushButton { background: #0f766e; color: white; border-radius:8px; }
      QPushButton:checked { background: #00d1b2; color: black; }
    )";
    qApp->setStyleSheet(s);
}

void MainWindow::onTick(){
    // update clock
    m_clockLabel->setText(QDateTime::currentDateTime().toString("dddd, dd MMM yyyy | HH:mm:ss"));

    // simulated sensors (replace with real data feed)
    double temp = 22.0 + (QRandomGenerator::global()->bounded(0, 100)) / 10.0;
    double ldr = QRandomGenerator::global()->bounded(1024);
    bool motion = (QRandomGenerator::global()->bounded(10)) > 6; // ~30% chance
    onNewTemp(temp);
    onNewLdr(ldr);
    onMotionChanged(motion);
}

void MainWindow::onNewTemp(double val){
    m_tempBig->setText(QString("Temp: %1 °C").arg(QString::number(val,'f',1)));
    m_tempSeries->append(m_index, val);
    m_index++;
    if(m_tempSeries->count() > 60) m_tempSeries->remove(0);
}

void MainWindow::onNewLdr(double val){
    m_ldrBig->setText(QString("LDR: %1").arg((int)val));
    m_ldrSeries->append(m_index, val);
    if(m_ldrSeries->count() > 60) m_ldrSeries->remove(0);
}

void MainWindow::onMotionChanged(bool detected){
    m_statusMotion->setText(QString("Motion: %1").arg(detected ? "Detected" : "No"));
    if(detected){
        m_statusMotion->setStyleSheet("color:#FF6B6B; font-weight:bold;");
    } else {
        m_statusMotion->setStyleSheet("color:#9AD6FF;");
    }
}

void MainWindow::onLedButton(){
    QPushButton *b = qobject_cast<QPushButton*>(sender());
    if(!b) return;
    bool on = b->isChecked();
    b->setText(QString("%1").arg(on ? "LED ON" : "LED OFF"));
    // TODO: publish MQTT or call GPIO helper. For demo we just toggle UI.
}

void MainWindow::onMjpegFrame(const QImage &img){
    QPixmap px = QPixmap::fromImage(img).scaled(m_cameraLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_cameraLabel->setPixmap(px);
}
