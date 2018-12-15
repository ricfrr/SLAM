
#include "../Headers/PriorityPointCloud.hpp"

PriorityPointCloud::PriorityPointCloud(int priority, pcl::PointCloud<pcl::PointXYZ>::Ptr source) {
    this->priority = priority;
    this->cloud = source;
};

PriorityPointCloud::~PriorityPointCloud() {

};

int PriorityPointCloud::getPriority() {
    return this->priority;
};

pcl::PointCloud<pcl::PointXYZ>::Ptr PriorityPointCloud::getPointCloud() {
    return this->cloud;
}
