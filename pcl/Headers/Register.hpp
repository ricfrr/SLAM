#ifndef Register_hpp
#define Register_hpp

#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <string>
#include <chrono>
#include <thread>

#include "Utilities.hpp"
#include "BruteICP.hpp"
#include "NormalICP.hpp"
#include "PriorityPointCloud.hpp"
#include "PriorityCloudComparator.hpp"
#include "Noise.hpp"


class Register {

public:
    Register();

    Register(int alg,
             std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
             std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points);

    Register(std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
             std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points);

    ~Register();

    //perform the actual registration
    void registration();

    BruteICP * getBruteICP();
    NormalICP* getNormalICP();
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr getRegisteredPoints();

    void resetRegisteredPoint();
    int getAlgorithm();
    void setAlgorithm(int _alg);
private:
    int alg = 0;
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points = nullptr;
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points = nullptr;

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr registered;

    Eigen::Matrix4f transformation = Eigen::Matrix4f::Identity();

    Noise noise = Noise();
    BruteICP bruteICP = BruteICP();
    NormalICP normalICP = NormalICP();
    Utilities utilities;

};

#endif /* PriorityPointCloud_hpp */
