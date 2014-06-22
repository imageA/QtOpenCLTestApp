#include "ui_mainwindow.h"
#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Ui::MainWindow ui;
    //MainWindow *w = new MainWindow();
    //ui.setupUi(w);
    //w->show();
    MainWindow w;
    w.show();

    return a.exec();
}

