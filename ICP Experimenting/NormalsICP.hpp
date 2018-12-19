//
//  NormalsICP.hpp
//  PointCloudProject
//
//  Created by Air Marvin on 18.12.18.
//  Copyright © 2018 Air Marvin. All rights reserved.
//

#ifndef NormalsICP_hpp
#define NormalsICP_hpp

#include <stdio.h>
#include <iostream>

#include <pcl/registration/icp.h>
#include <pcl/io/pcd_io.h>

#include <pcl/point_types.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace pcl;

class NormalsICP {
    
public:
    NormalsICP();
    ~NormalsICP();
    
    PointCloud<pcl::PointXYZ>::Ptr source_cloud;
    PointCloud<pcl::PointXYZ>::Ptr target_cloud;
    PointCloud<pcl::PointNormal>::Ptr result_cloud;
    
    pcl::PCLBase<pcl::PointNormal>::PointCloudConstPtr cloud_source;
    pcl::PCLBase<pcl::PointNormal>::PointCloudConstPtr  cloud_target;
    
    IterativeClosestPointWithNormals<PointNormal,PointNormal> * icp;
    
    void convertCloud(PointCloud<pcl::PointXYZ>::Ptr &source, PointCloud<PointNormal> &target);
};

#endif /* NormalsICP_hpp */
