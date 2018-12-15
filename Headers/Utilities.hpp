#ifndef Utilities_hpp
#define Utilities_hpp


#include <vector>
#include <pcl/io/pcd_io.h>
#include <pcl/io/io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/common/transforms.h>
#include <pcl/features/normal_3d.h>
#include <vtkRenderWindow.h>
#include <vtkRendererCollection.h>
#include <vtkCamera.h>
#include <pcl/filters/voxel_grid.h>
#include <string>
#include "PriorityPointCloud.hpp"
#include <queue>

class Utilities {

public:
    Utilities();

    ~Utilities();

    std::vector<std::string> split(const std::string &str, const std::string &delim);

    PriorityPointCloud fromStringToPriorityPointCloud(const std::string &st);

    void loadFile(const std::string fileName, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void saveFile(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud);

    void saveFile(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr &cloud);

    void showCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void showCloud(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud);

    void refreshShowCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void refreshShowCloud(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud);

    void downScale(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);

    void downScale(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud);


    void transform(pcl::PointCloud<pcl::PointXYZ>::Ptr source);

    void continueShowCloud();

private:
    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
    pcl::VoxelGrid<pcl::PointXYZ> sor;
    pcl::VoxelGrid<pcl::PointXYZRGBNormal> sor_normal;

};

#endif /* Utilities_hpp */
