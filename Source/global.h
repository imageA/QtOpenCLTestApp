#ifndef GLOBAL_H
#define GLOBAL_H

#define OPENCL_CL_OFF_H 0
#define OPENCL_CL_ON_H 1

#define QT_EXAMPLE_SQUARE_H 0
#define QT_EXAMPLE_HOG_H 1

#include <QMainWindow>
#include <opencv2/core/core.hpp>

//QImage Mat2QImage(cv::Mat const& src);
QImage Mat2QImage(const cv::Mat3b &src);

#endif // GLOBAL_H
