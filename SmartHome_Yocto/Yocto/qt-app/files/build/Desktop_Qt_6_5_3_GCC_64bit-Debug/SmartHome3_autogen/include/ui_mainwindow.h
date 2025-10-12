/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *sun;
    QLabel *red;
    QSlider *LM35_2;
    QLabel *LDR;
    QLabel *yellow;
    QLabel *LDRvalue;
    QDial *LDR_2;
    QLabel *green;
    QLabel *motion;
    QLabel *LM35value;
    QLabel *LM35;
    QCheckBox *CheckBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 853);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sun = new QLabel(centralwidget);
        sun->setObjectName("sun");
        sun->setGeometry(QRect(750, 150, 251, 191));
        red = new QLabel(centralwidget);
        red->setObjectName("red");
        red->setGeometry(QRect(270, 240, 121, 81));
        LM35_2 = new QSlider(centralwidget);
        LM35_2->setObjectName("LM35_2");
        LM35_2->setGeometry(QRect(250, 240, 21, 301));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(10);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(LM35_2->sizePolicy().hasHeightForWidth());
        LM35_2->setSizePolicy(sizePolicy);
        LM35_2->setMaximumSize(QSize(21, 16777215));
        LM35_2->setSizeIncrement(QSize(5, 0));
        LM35_2->setBaseSize(QSize(0, 0));
        LM35_2->setMouseTracking(false);
        LM35_2->setOrientation(Qt::Vertical);
        LDR = new QLabel(centralwidget);
        LDR->setObjectName("LDR");
        LDR->setGeometry(QRect(820, 580, 91, 31));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        LDR->setFont(font);
        yellow = new QLabel(centralwidget);
        yellow->setObjectName("yellow");
        yellow->setGeometry(QRect(1020, 220, 131, 71));
        LDRvalue = new QLabel(centralwidget);
        LDRvalue->setObjectName("LDRvalue");
        LDRvalue->setGeometry(QRect(840, 390, 111, 71));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        LDRvalue->setFont(font1);
        LDR_2 = new QDial(centralwidget);
        LDR_2->setObjectName("LDR_2");
        LDR_2->setGeometry(QRect(720, 270, 261, 311));
        LDR_2->setAutoFillBackground(true);
        LDR_2->setMaximum(1023);
        LDR_2->setValue(0);
        LDR_2->setSliderPosition(0);
        LDR_2->setOrientation(Qt::Horizontal);
        LDR_2->setInvertedAppearance(false);
        LDR_2->setWrapping(false);
        LDR_2->setNotchesVisible(true);
        green = new QLabel(centralwidget);
        green->setObjectName("green");
        green->setGeometry(QRect(1020, 300, 131, 81));
        green->setMaximumSize(QSize(131, 81));
        motion = new QLabel(centralwidget);
        motion->setObjectName("motion");
        motion->setGeometry(QRect(1090, 220, 121, 71));
        LM35value = new QLabel(centralwidget);
        LM35value->setObjectName("LM35value");
        LM35value->setGeometry(QRect(290, 300, 111, 71));
        LM35value->setFont(font1);
        LM35 = new QLabel(centralwidget);
        LM35->setObjectName("LM35");
        LM35->setGeometry(QRect(230, 580, 91, 31));
        LM35->setFont(font);
        CheckBox = new QCheckBox(centralwidget);
        CheckBox->setObjectName("CheckBox");
        CheckBox->setGeometry(QRect(1020, 460, 91, 23));
        MainWindow->setCentralWidget(centralwidget);
        sun->raise();
        red->raise();
        LM35_2->raise();
        LDR->raise();
        yellow->raise();
        green->raise();
        motion->raise();
        LM35value->raise();
        LM35->raise();
        LDR_2->raise();
        LDRvalue->raise();
        CheckBox->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1280, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        sun->setText(QCoreApplication::translate("MainWindow", "sun", nullptr));
        red->setText(QCoreApplication::translate("MainWindow", "red", nullptr));
        LDR->setText(QCoreApplication::translate("MainWindow", "LDR", nullptr));
        yellow->setText(QCoreApplication::translate("MainWindow", "yellow", nullptr));
        LDRvalue->setText(QCoreApplication::translate("MainWindow", "LDRvalue", nullptr));
        green->setText(QCoreApplication::translate("MainWindow", "green", nullptr));
        motion->setText(QCoreApplication::translate("MainWindow", "motion", nullptr));
        LM35value->setText(QCoreApplication::translate("MainWindow", "LM35value", nullptr));
        LM35->setText(QCoreApplication::translate("MainWindow", "LM35", nullptr));
        CheckBox->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
