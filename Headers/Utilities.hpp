#ifndef Utilities_hpp
#define Utilities_hpp

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


class Utilities {

public:
    Utilities();

    ~Utilities();

    void loadFile(const std::string fileName, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void saveFile(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);

    void showCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void refreshShowCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void downScale(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void continueShowCloud();

private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::VoxelGrid<pcl::PointXYZ> sor;

};

#endif /* Utilities_hpp */
