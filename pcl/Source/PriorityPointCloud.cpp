
#include "../Headers/PriorityPointCloud.hpp"

PriorityPointCloud::PriorityPointCloud(int priority, pcl::PointCloud<pcl::PointXYZRGB>::Ptr source) {
    this->priority = priority;
    this->cloud = source;
};

PriorityPointCloud::~PriorityPointCloud() {

};

int PriorityPointCloud::getPriority() {
    return this->priority;
};

pcl::PointCloud<pcl::PointXYZRGB>::Ptr PriorityPointCloud::getPointCloud() {
    return this->cloud;
}
