#ifndef BruteICP_hpp
#define BruteICP_hpp

#include <vector>

#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/voxel_grid.h>
#include <string>

#include "Utilities.hpp"

class BruteICP {

public:
    BruteICP();

    ~BruteICP();

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr bruteIcpRegistration (pcl::PointCloud<pcl::PointXYZRGB>::Ptr source, pcl::PointCloud<pcl::PointXYZRGB>::Ptr target);

    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB>::Ptr getICP();

    void resetTransformationMatrix();

    void setTransformationMatrix(Eigen::Matrix4f * _transformation);


private:
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB>::Ptr icp;
    Eigen::Matrix4f* transformation;
    Utilities utilities;
};

#endif /* BruteICP_hpp */
