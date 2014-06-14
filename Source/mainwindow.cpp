#include "mainwindow.h"
#include "ui_mainwindow.h"

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
    }
    else if(index == QT_EXAMPLE_HOG_H)
    {
    }

    ui->te_Result->setText( result );

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

