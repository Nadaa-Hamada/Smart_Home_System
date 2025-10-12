

#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include <QSplashScreen>
#include <QPixmap>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPixmap pixmap(":/Icons/splash.jpeg");
    QSplashScreen splash(pixmap);
    splash.showMessage("Loading Smart Home Dashboard...",
                       Qt::AlignBottom | Qt::AlignCenter,
                       Qt::white);
    splash.show();

    QTimer::singleShot(4000, &a, [&]() {
        MainWindow *w = new MainWindow();
        w->show(); // show the smart home dashboard
        splash.finish(w);
    });

    return a.exec();
}
