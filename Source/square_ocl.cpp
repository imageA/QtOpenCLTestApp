#include "square_ocl.h"

double SquareOcl::angle( Point pt1, Point pt2, Point pt0 )
{
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void SquareOcl::draw_squares( Mat& image, const vector<vector<Point> >& squares )
{
    for( size_t i = 0; i < squares.size(); i++ )
    {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(image, &p, &n, 1, true, Scalar(0,255,0), 3, CV_AA);
    }
}

void SquareOcl::find_squares_gpu( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat gray;
    cv::ocl::oclMat pyr_ocl, timg_ocl, gray0_ocl, gray_ocl;

    // down-scale and upscale the image to filter out the noise
    ocl::pyrDown(ocl::oclMat(image), pyr_ocl);
    ocl::pyrUp(pyr_ocl, timg_ocl);

    vector<vector<Point> > contours;
    vector<cv::ocl::oclMat> gray0s;
    ocl::split(timg_ocl, gray0s); // split 3 channels into a vector of oclMat
    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        gray0_ocl = gray0s[c];
        // try several threshold levels
        for( int l = 0; l < SQUARE_OCL_THRESH_LEVEL_H; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // do canny on OpenCL device
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                cv::ocl::Canny(gray0_ocl, gray_ocl, 0, SQUARE_OCL_EDGE_THRESH_H, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                ocl::dilate(gray_ocl, gray_ocl, Mat(), Point(-1,-1));
                gray = Mat(gray_ocl);
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                cv::ocl::threshold(gray0_ocl, gray_ocl, (l+1)*255/SQUARE_OCL_THRESH_LEVEL_H, 255, THRESH_BINARY);
                gray = gray_ocl;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;
            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                        fabs(contourArea(Mat(approx))) > 1000 &&
                        isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
}

void SquareOcl::find_squares_cpu( const Mat& image, vector<vector<Point> >& squares )
{
    squares.clear();

    Mat pyr, timg, gray0(image.size(), CV_8U), gray;

    // down-scale and upscale the image to filter out the noise
    pyrDown(image, pyr, Size(image.cols/2, image.rows/2));
    pyrUp(pyr, timg, image.size());
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for( int c = 0; c < 3; c++ )
    {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        for( int l = 0; l < SQUARE_OCL_THRESH_LEVEL_H; l++ )
        {
            // hack: use Canny instead of zero threshold level.
            // Canny helps to catch squares with gradient shading
            if( l == 0 )
            {
                // apply Canny. Take the upper threshold from slider
                // and set the lower to 0 (which forces edges merging)
                Canny(gray0, gray, 0, SQUARE_OCL_EDGE_THRESH_H, 5);
                // dilate canny output to remove potential
                // holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                // apply threshold if l!=0:
                //     tgray(x,y) = gray(x,y) < (l+1)*255/N ? 255 : 0
                gray = gray0 >= (l+1)*255/SQUARE_OCL_THRESH_LEVEL_H;
            }

            // find contours and store them all as a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            vector<Point> approx;

            // test each contour
            for( size_t i = 0; i < contours.size(); i++ )
            {
                // approximate contour with accuracy proportional
                // to the contour perimeter
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                // square contours should have 4 vertices after approximation
                // relatively large area (to filter out noisy contours)
                // and be convex.
                // Note: absolute value of an area is used because
                // area may be positive or negative - in accordance with the
                // contour orientation
                if( approx.size() == 4 &&
                        fabs(contourArea(Mat(approx))) > 1000 &&
                        isContourConvex(Mat(approx)) )
                {
                    double maxCosine = 0;

                    for( int j = 2; j < 5; j++ )
                    {
                        // find the maximum cosine of the angle between joint edges
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    // if cosines of all angles are small
                    // (all angles are ~90 degree) then write quandrange
                    // vertices to resultant sequence
                    if( maxCosine < 0.3 )
                        squares.push_back(approx);
                }
            }
        }
    }
}


QString SquareOcl::start_preview(int operate_type, QLabel* lb_image)
{
    QString str_result = "";

    Mat mat_image = imread(SQUARE_OCL_FILE_SRC, 1);
    vector<vector<Point> > squares;
    long start_time, end_time;

    if(mat_image.empty())
    {
        str_result = "Couldn't load ";
        str_result.append(SQUARE_OCL_FILE_SRC);
        return str_result;
    }

    if(operate_type == OPENCL_CL_OFF_H)
    {
        start_time = getTickCount();
        find_squares_cpu(mat_image, squares);
        end_time = getTickCount();
    }
    else if(operate_type == OPENCL_CL_ON_H)
    {
        // OCL Init
        vector<ocl::Info> info;
        CV_Assert(cv::ocl::getDevice(info));
        start_time = getTickCount();
        find_squares_gpu(mat_image, squares);
        end_time = getTickCount();
    }
    else
    {
        str_result = "Not Operate Mode!!";
        return str_result;
    }

    draw_squares(mat_image, squares);

    QImage tmp_image = Mat2QImage(mat_image);

    lb_image->setPixmap(QPixmap::fromImage(tmp_image));

    str_result = QString("Find Search Result : \n - Square Count : ") + QString::number(squares.size());
    str_result = str_result + QString("\n - Search Time : ");
    str_result = str_result + QString::number(1000.0f * (double)(end_time - start_time) / getTickFrequency() / 10 ).append("ms");
    return str_result;
}
