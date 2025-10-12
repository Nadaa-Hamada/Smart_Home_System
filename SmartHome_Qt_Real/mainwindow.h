#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialreader.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateSensors(int temp, int light);
    void checkMotion();

private:
    Ui::MainWindow *ui;
    SerialReader *serialReader;

    int mockMotionValue = 0; // القيمة الوهمية للحركة

};

#endif // MAINWINDOW_H
