/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLineEdit *inputMiasto;
    QPushButton *buttonPobierzStacje;
    QComboBox *comboStacje;
    QTextEdit *textWyniki;
    QComboBox *comboSensory;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *buttonPobierzDane;
    QFrame *chartView;
    QPushButton *buttonOffline;
    QComboBox *comboZakres;
    QDateEdit *dateOd;
    QDateEdit *dateDo;
    QLabel *LabelOd;
    QLabel *LabelDo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1149, 595);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        inputMiasto = new QLineEdit(centralwidget);
        inputMiasto->setObjectName("inputMiasto");
        inputMiasto->setGeometry(QRect(30, 70, 331, 28));
        buttonPobierzStacje = new QPushButton(centralwidget);
        buttonPobierzStacje->setObjectName("buttonPobierzStacje");
        buttonPobierzStacje->setGeometry(QRect(380, 70, 111, 29));
        comboStacje = new QComboBox(centralwidget);
        comboStacje->setObjectName("comboStacje");
        comboStacje->setGeometry(QRect(30, 150, 291, 21));
        textWyniki = new QTextEdit(centralwidget);
        textWyniki->setObjectName("textWyniki");
        textWyniki->setGeometry(QRect(730, 110, 371, 451));
        comboSensory = new QComboBox(centralwidget);
        comboSensory->setObjectName("comboSensory");
        comboSensory->setGeometry(QRect(360, 150, 161, 21));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 120, 121, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 50, 121, 21));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(380, 120, 121, 21));
        buttonPobierzDane = new QPushButton(centralwidget);
        buttonPobierzDane->setObjectName("buttonPobierzDane");
        buttonPobierzDane->setGeometry(QRect(560, 140, 111, 29));
        chartView = new QFrame(centralwidget);
        chartView->setObjectName("chartView");
        chartView->setGeometry(QRect(40, 260, 641, 301));
        chartView->setFrameShape(QFrame::Shape::StyledPanel);
        chartView->setFrameShadow(QFrame::Shadow::Raised);
        buttonOffline = new QPushButton(centralwidget);
        buttonOffline->setObjectName("buttonOffline");
        buttonOffline->setGeometry(QRect(560, 70, 121, 31));
        comboZakres = new QComboBox(centralwidget);
        comboZakres->setObjectName("comboZakres");
        comboZakres->setGeometry(QRect(40, 200, 161, 28));
        dateOd = new QDateEdit(centralwidget);
        dateOd->setObjectName("dateOd");
        dateOd->setGeometry(QRect(250, 220, 110, 29));
        dateDo = new QDateEdit(centralwidget);
        dateDo->setObjectName("dateDo");
        dateDo->setGeometry(QRect(390, 220, 110, 29));
        LabelOd = new QLabel(centralwidget);
        LabelOd->setObjectName("LabelOd");
        LabelOd->setGeometry(QRect(270, 190, 63, 20));
        LabelDo = new QLabel(centralwidget);
        LabelDo->setObjectName("LabelDo");
        LabelDo->setGeometry(QRect(410, 190, 63, 20));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        buttonPobierzStacje->setText(QCoreApplication::translate("MainWindow", "Pobierz stacje", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Wybierz stacje", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Wybierz miasto", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Wybierz czujnik", nullptr));
        buttonPobierzDane->setText(QCoreApplication::translate("MainWindow", "Pobierz dane", nullptr));
        buttonOffline->setText(QCoreApplication::translate("MainWindow", "Offline", nullptr));
        LabelOd->setText(QCoreApplication::translate("MainWindow", "Data od", nullptr));
        LabelDo->setText(QCoreApplication::translate("MainWindow", "Data do", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
