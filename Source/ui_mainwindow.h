/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Jun 8 10:12:49 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QLabel *lb_View;
    QComboBox *cb_ExampleList;
    QPushButton *bt_Start;
    QGroupBox *gb_OpType;
    QRadioButton *rb_cl_on;
    QRadioButton *rb_cl_off;
    QGroupBox *gb_Result;
    QTextEdit *te_Result;
    QLabel *lb_Version;
    QPushButton *bt_Stop;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(623, 579);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 60, 400, 300));
        frame->setMinimumSize(QSize(400, 300));
        frame->setMaximumSize(QSize(400, 300));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        frame->setPalette(palette);
        frame->setStyleSheet(QString::fromUtf8("background-color: black"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        lb_View = new QLabel(frame);
        lb_View->setObjectName(QString::fromUtf8("lb_View"));
        lb_View->setGeometry(QRect(0, 0, 400, 300));
        cb_ExampleList = new QComboBox(centralWidget);
        cb_ExampleList->setObjectName(QString::fromUtf8("cb_ExampleList"));
        cb_ExampleList->setGeometry(QRect(10, 30, 401, 27));
        cb_ExampleList->setEditable(false);
        cb_ExampleList->setMinimumContentsLength(0);
        cb_ExampleList->setFrame(true);
        bt_Start = new QPushButton(centralWidget);
        bt_Start->setObjectName(QString::fromUtf8("bt_Start"));
        bt_Start->setGeometry(QRect(430, 30, 81, 27));
        gb_OpType = new QGroupBox(centralWidget);
        gb_OpType->setObjectName(QString::fromUtf8("gb_OpType"));
        gb_OpType->setGeometry(QRect(430, 70, 191, 61));
        gb_OpType->setStyleSheet(QString::fromUtf8(""));
        gb_OpType->setFlat(false);
        gb_OpType->setCheckable(false);
        rb_cl_on = new QRadioButton(gb_OpType);
        rb_cl_on->setObjectName(QString::fromUtf8("rb_cl_on"));
        rb_cl_on->setGeometry(QRect(10, 30, 71, 22));
        rb_cl_on->setChecked(true);
        rb_cl_off = new QRadioButton(gb_OpType);
        rb_cl_off->setObjectName(QString::fromUtf8("rb_cl_off"));
        rb_cl_off->setGeometry(QRect(100, 30, 81, 22));
        gb_Result = new QGroupBox(centralWidget);
        gb_Result->setObjectName(QString::fromUtf8("gb_Result"));
        gb_Result->setGeometry(QRect(10, 370, 601, 131));
        te_Result = new QTextEdit(gb_Result);
        te_Result->setObjectName(QString::fromUtf8("te_Result"));
        te_Result->setGeometry(QRect(0, 20, 591, 101));
        te_Result->setReadOnly(false);
        lb_Version = new QLabel(centralWidget);
        lb_Version->setObjectName(QString::fromUtf8("lb_Version"));
        lb_Version->setGeometry(QRect(10, 0, 241, 17));
        bt_Stop = new QPushButton(centralWidget);
        bt_Stop->setObjectName(QString::fromUtf8("bt_Stop"));
        bt_Stop->setGeometry(QRect(530, 30, 81, 27));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 623, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        cb_ExampleList->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "QT Open CV & CL TEST", 0, QApplication::UnicodeUTF8));
        lb_View->setText(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        cb_ExampleList->clear();
        cb_ExampleList->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "SQUARE", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "HOG", 0, QApplication::UnicodeUTF8)
        );
        bt_Start->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        gb_OpType->setTitle(QApplication::translate("MainWindow", "CL On&&Off", 0, QApplication::UnicodeUTF8));
        rb_cl_on->setText(QApplication::translate("MainWindow", "CL ON", 0, QApplication::UnicodeUTF8));
        rb_cl_off->setText(QApplication::translate("MainWindow", "CL OFF", 0, QApplication::UnicodeUTF8));
        gb_Result->setTitle(QApplication::translate("MainWindow", "RESULT", 0, QApplication::UnicodeUTF8));
        lb_Version->setText(QApplication::translate("MainWindow", "<html><head/><body><p>OpenCV Version : </p></body></html>", 0, QApplication::UnicodeUTF8));
        bt_Stop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
