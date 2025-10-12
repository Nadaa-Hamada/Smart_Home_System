#pragma once
#include <QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QChart>
#include <QtCharts/QPieSeries>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>

QT_USE_NAMESPACE


    class MJPEGReceiver : public QObject {
    Q_OBJECT
public:
    MJPEGReceiver(const QUrl &url, QObject *parent = nullptr);
    ~MJPEGReceiver();
    QImage latestFrame() const;
signals:
    void frameReady(const QImage &img);
    void errorOccured(const QString &err);
public slots:
    void start();
    void stop();
private slots:
    void readyRead();
    void finished();
private:
    QUrl m_url;
    QNetworkAccessManager m_nam;
    QNetworkReply *m_reply = nullptr;
    QByteArray m_buffer;
    QImage m_frame;
    QString m_boundary;
    void parseBoundary(const QByteArray &buf);
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onTick(); // updates clock + simulated sensors
    void onNewTemp(double val);
    void onNewLdr(double val);
    void onMotionChanged(bool detected);
    void onLedButton();
    void onMjpegFrame(const QImage &img);

private:
    void setupUi();
    void setupCharts();
    void applyDarkStyle();

    // UI widgets
    QLabel *m_clockLabel;
    QLabel *m_statusMotion;
    QLabel *m_tempBig;
    QLabel *m_ldrBig;
    QLabel *m_cameraLabel; // shows current camera frame (MJPEG)
    QPushButton *m_ledButtons[4];

    // Charts
    QChart *m_tempChart;
    QLineSeries *m_tempSeries;
    QChartView *m_tempChartView;

    QChart *m_ldrChart;
    QLineSeries *m_ldrSeries;
    QChartView *m_ldrChartView;

    // timers + simulated sensors
    QTimer m_timer;
    qint64 m_index = 0;

    // MJPEG receiver (optional)
    MJPEGReceiver *m_mjpeg = nullptr;
};
