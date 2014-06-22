#include "ui_mainwindow.h"
#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Start()
{
    int index = ui->cb_ExampleList->currentIndex();
    QString result = "";

    if(index == QT_EXAMPLE_SQUARE_H)
    {
        SquareOcl square_ocl;
        ui->lb_View->setPixmap(NULL);
        if(ui->rb_cl_on->isChecked())
            result = square_ocl.start_preview(OPENCL_CL_ON_H, ui->lb_View);
        else
            result = square_ocl.start_preview(OPENCL_CL_OFF_H, ui->lb_View);

        ui->te_Result->setText( result );
    }
    else if(index == QT_EXAMPLE_HOG_H)
    {
    }
    else if(index == QT_EXAMPLE_PERFORMANCE_H)
    {
        PerformanceOcl performance_ocl;
        performance_ocl.set_result_test(ui->te_Result);
        performance_ocl.set_tests_filter(ui->cb_LibraryList->currentText().toUtf8().constData());
        performance_ocl.start_performance_test();
    }


}

void MainWindow::Stop()
{
    int index = ui->cb_ExampleList->currentIndex();

    if(index == QT_EXAMPLE_SQUARE_H)
    {
        ui->lb_View->setPixmap(NULL);
    }
    else if(index == QT_EXAMPLE_HOG_H)
    {
    }
}

void MainWindow::Init()
{
    ui->gb_oclList->setVisible(false);

    // Event
    connect(ui->bt_Start,SIGNAL(clicked()), this, SLOT(Start()));
    connect(ui->bt_Stop,SIGNAL(clicked()), this, SLOT(Stop()));

    // OpenCV Version
    ui->lb_Version->setText(QString("OpenCV Version : ").append(CV_VERSION));
}

// OpenCV Porting Simply Test
void MainWindow::OpenCVTest()
{
    imagerd = cvLoadImage("./pic1.png");
    QImage image = QImage((const unsigned char*)(imagerd->imageData), imagerd->width,imagerd->height,QImage::Format_RGB888).rgbSwapped();
    ui->lb_View->setPixmap(QPixmap::fromImage(image));

}


void MainWindow::on_cb_ExampleList_currentIndexChanged(int index)
{
    if(index == 3)
    {
        ui->gb_oclList->setVisible(false);
    }
    else
    {
        ui->gb_oclList->setVisible(true);
    }
}
