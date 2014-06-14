#ifndef SQUARE_OCL_H
#define SQUARE_OCL_H

#define SQUARE_OCL_EDGE_THRESH_H 50
#define SQUARE_OCL_THRESH_LEVEL_H 3
#define SQUARE_OCL_FILE_SRC "pic1.png"

#include <QLabel>
#include <QTextEdit>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/ocl/ocl.hpp"

#include <iostream>
#include <math.h>
#include <string.h>


#include "global.h"

using namespace cv;
using namespace std;

class SquareOcl
{
public:
    QString start_preview(int operate_type, QLabel* lb_image);

private:
    double angle( Point pt1, Point pt2, Point pt0 );
    void draw_squares( Mat& image, const vector<vector<Point> >& squares );
    void find_squares_gpu( const Mat& image, vector<vector<Point> >& squares );
    void find_squares_cpu( const Mat& image, vector<vector<Point> >& squares );

};

#endif // SQUARE_OCL_H
