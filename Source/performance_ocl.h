#ifndef PERFORMANCE_OCL_H
#define PERFORMANCE_OCL_H

#include <QTextEdit>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/features2d/features2d.hpp"

#define USE_OPENCL 1
#define TAB "    "

#ifdef USE_OPENCL
#include "opencv2/ocl/ocl.hpp"
#endif

class PerformanceOcl
{
private:
    std::string filter_name;
    QTextEdit* te_result;

public:
    std::stringstream result;

public:
    PerformanceOcl();

    void set_result_test(QTextEdit* te_result);
    void set_tests_filter(std::string filter_name);
    QString start_performance_test();

};

class Runnable
{
public:
    explicit Runnable(const std::string &runname): name_(runname) {}
    virtual ~Runnable() {}

    const std::string &name() const
    {
        return name_;
    }

    virtual void run() = 0;

private:
    std::string name_;
};

class TestSystem
{
public:


    static TestSystem &instance()
    {

        static TestSystem me;

        return me;
    }

    void TESTINIT()
    {
        num_subtests_called_ = 0;

        speedup_total_ = 0;
        speedup_full_total_ = 0;
        num_subtests_called_ = 0;

        speedup_faster_count_ = 0;
        speedup_slower_count_ = 0;
        speedup_equal_count_ = 0;

        speedup_full_faster_count_ = 0;
        speedup_full_slower_count_ = 0;
        speedup_full_equal_count_ = 0;

    }

    void setWorkingDir(const std::string &val)
    {
        working_dir_ = val;
    }
    const std::string &workingDir()
    {
        return working_dir_;
    }

    void setTestFilter(const std::string &val)
    {
        test_filter_ = val;
    }
    const std::string &testFilter() const
    {
        return test_filter_;
    }

    void setNumIters(int num_iters)
    {
        num_iters_ = num_iters;
    }
    void setGPUWarmupIters(int num_iters)
    {
        gpu_warmup_iters_ = num_iters;
    }
    void setCPUIters(int num_iters)
    {
        cpu_num_iters_ = num_iters;
    }

    void setTopThreshold(double top)
    {
        top_ = top;
    }
    void setBottomThreshold(double bottom)
    {
        bottom_ = bottom;
    }

    void addInit(Runnable *init)
    {
        inits_.push_back(init);
    }
    void addTest(Runnable *test)
    {
        tests_.push_back(test);
    }
    void run();

    // It's public because OpenCV callback uses it
    void printError(const std::string &msg);

    std::stringstream &startNewSubtest()
    {
        finishCurrentSubtest();
        return cur_subtest_description_;
    }

    bool stop() const
    {
        return cur_iter_idx_ >= num_iters_;
    }

    bool cpu_stop() const
    {
        return cur_iter_idx_ >= cpu_num_iters_;
    }

    bool warmupStop()
    {
        return cur_warmup_idx_++ >= gpu_warmup_iters_;
    }

    void warmupComplete()
    {
        cur_warmup_idx_ = 0;
    }

    void cpuOn()
    {
        cpu_started_ = cv::getTickCount();
    }
    void cpuOff()
    {
        long delta = cv::getTickCount() - cpu_started_;
        cpu_times_.push_back(delta);
        ++cur_iter_idx_;
    }
    void cpuComplete()
    {
        cpu_elapsed_ += meanTime(cpu_times_);
        cur_subtest_is_empty_ = false;
        cur_iter_idx_ = 0;
    }

    void gpuOn()
    {
        gpu_started_ = cv::getTickCount();
    }
    void gpuOff()
    {
        long delta = cv::getTickCount() - gpu_started_;
        gpu_times_.push_back(delta);
        ++cur_iter_idx_;
    }
    void gpuComplete()
    {
        gpu_elapsed_ += meanTime(gpu_times_);
        cur_subtest_is_empty_ = false;
        cur_iter_idx_ = 0;
    }

    void gpufullOn()
    {
        gpu_full_started_ = cv::getTickCount();
    }
    void gpufullOff()
    {
        long delta = cv::getTickCount() - gpu_full_started_;
        gpu_full_times_.push_back(delta);
        ++cur_iter_idx_;
    }
    void gpufullComplete()
    {
        gpu_full_elapsed_ += meanTime(gpu_full_times_);
        cur_subtest_is_empty_ = false;
        cur_iter_idx_ = 0;
    }

    bool isListMode() const
    {
        return is_list_mode_;
    }
    void setListMode(bool value)
    {
        is_list_mode_ = value;
    }

    void setRecordName(const std::string &name)
    {
        recordname_ = name;
    }

    void setCurrentTest(const std::string &name)
    {
        itname_ = name;
        itname_changed_ = true;
    }

    std::stringstream results;

    void resetCurrentSubtest()
    {
        cpu_elapsed_ = 0;
        gpu_elapsed_ = 0;
        gpu_full_elapsed_ = 0;
        cur_subtest_description_.str("");
        cur_subtest_is_empty_ = true;
        cur_iter_idx_ = 0;
        cpu_times_.clear();
        gpu_times_.clear();
        gpu_full_times_.clear();
    }

private:
    TestSystem():
        cur_subtest_is_empty_(true), cpu_elapsed_(0),
        gpu_elapsed_(0), gpu_full_elapsed_(0), speedup_total_(0.0),
        num_subtests_called_(0),
        speedup_faster_count_(0), speedup_slower_count_(0), speedup_equal_count_(0),
        speedup_full_faster_count_(0), speedup_full_slower_count_(0), speedup_full_equal_count_(0), is_list_mode_(false),
        num_iters_(10), cpu_num_iters_(2),
        gpu_warmup_iters_(1), cur_iter_idx_(0), cur_warmup_idx_(0),
        record_(0), recordname_("performance"), itname_changed_(true)
    {
        cpu_times_.reserve(num_iters_);
        gpu_times_.reserve(num_iters_);
        gpu_full_times_.reserve(num_iters_);
    }

    void finishCurrentSubtest();


    double meanTime(const std::vector<long> &samples);

    void printHeading();
    void printSummary();
    void printMetrics(double cpu_time, double gpu_time, double gpu_full_time, double speedup, double fullspeedup);

    void writeHeading();
    void writeSummary();
    void writeMetrics(double cpu_time, double gpu_time, double gpu_full_time,
                      double speedup, double fullspeedup,
                      double gpu_min, double gpu_max, double std_dev);

    std::string working_dir_;
    std::string test_filter_;

    std::vector<Runnable *> inits_;
    std::vector<Runnable *> tests_;


    std::stringstream cur_subtest_description_;
    bool cur_subtest_is_empty_;

    long cpu_started_;
    long gpu_started_;
    long gpu_full_started_;
    double cpu_elapsed_;
    double gpu_elapsed_;
    double gpu_full_elapsed_;

    double speedup_total_;
    double speedup_full_total_;
    int num_subtests_called_;

    int speedup_faster_count_;
    int speedup_slower_count_;
    int speedup_equal_count_;

    int speedup_full_faster_count_;
    int speedup_full_slower_count_;
    int speedup_full_equal_count_;

    bool is_list_mode_;

    double top_;
    double bottom_;

    int num_iters_;
    int cpu_num_iters_;		//there's no need to set cpu running same times with gpu
    int gpu_warmup_iters_;	//gpu warm up times, default is 1
    int cur_iter_idx_;
    int cur_warmup_idx_;	//current gpu warm up times
    std::vector<long> cpu_times_;
    std::vector<long> gpu_times_;
    std::vector<long> gpu_full_times_;

    FILE *record_;
    std::string recordname_;
    std::string itname_;
    bool itname_changed_;
};


#endif // PERFORMANCE_OCL_H
