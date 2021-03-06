#ifndef PriorityPointCloud_hpp
#define PriorityPointCloud_hpp

#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <string>



class PriorityPointCloud {

public:
    PriorityPointCloud();

    PriorityPointCloud(int priority, pcl::PointCloud<pcl::PointXYZ>::Ptr source);

    ~PriorityPointCloud();

    pcl::PointCloud<pcl::PointXYZ>::Ptr getPointCloud();

    int getPriority();

    int priority;
private:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;

};

#endif /* PriorityPointCloud_hpp */
