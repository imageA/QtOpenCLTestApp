#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ocl/ocl.hpp>

#include "square_ocl.h"
#include "global.h"

using namespace cv;
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void Init();

private:
    void OpenCVTest();

private slots:
    void Start();
    void Stop();

public:

private:
    Ui::MainWindow *ui;
    IplImage*   imagerd;
};

#endif // MAINWINDOW_H
