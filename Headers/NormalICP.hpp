#ifndef NormalICP_hpp
#define NormalICP_hpp

#include <vector>

#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/point_types.h>
#include <pcl/registration/icp.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <pcl/filters/voxel_grid.h>
#include <string>

#include "Utilities.hpp"

class NormalICP {

public:
    NormalICP();
    ~NormalICP();

    pcl::PointCloud<pcl::PointXYZ>::Ptr normalIcpRegistration (pcl::PointCloud<pcl::PointXYZ>::Ptr source, pcl::PointCloud<pcl::PointXYZ>::Ptr target);

private:

    void addNormal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals);
    Utilities utilities;

};

#endif /* NormalICP_hpp */
