#ifndef NormalICP_hpp
#define NormalICP_hpp

#include <vector>

#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <pcl/filters/voxel_grid.h>
#include <string>

#include "Utilities.hpp"

class NormalICP {

public:
    NormalICP();
    ~NormalICP();

    pcl::PointCloud<pcl::PointXYZ>::Ptr normalIcpRegistration (pcl::PointCloud<pcl::PointXYZ>::Ptr source, pcl::PointCloud<pcl::PointXYZ>::Ptr target);

    void addNormal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals);

    pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>::Ptr getICP();

	void resetTransformationMatrix();

	void setTransformationMatrix(Eigen::Matrix4f * _transformation);

private:
    Utilities utilities;
    Eigen::Matrix4f* transformation;
	
	pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>::Ptr icp;
};

#endif /* NormalICP_hpp */
