//
//  NormalsICP.cpp
//  PointCloudProject
//
//  Created by Air Marvin on 18.12.18.
//  Copyright © 2018 Air Marvin. All rights reserved.
//

#include "NormalsICP.hpp"

NormalsICP::NormalsICP(){
    
    std::cout << "constructed an icp object with Normals" << std::endl;
    
    icp = new IterativeClosestPointWithNormals<PointNormal,PointNormal>();
    
    // Load the cloud and saves it into the global list of models
    PointCloud<PointNormal> source;
    PointCloud<PointNormal> target;
    
    
    PointCloud<PointXYZ> sourcexyz;
    io::loadPCDFile("source.pcd", sourcexyz);
    
    PointCloud<PointXYZ> targetxyz;
     io::loadPCDFile("target.pcd", targetxyz);
    
    source_cloud =  boost::make_shared<PointCloud<PointXYZ> >(sourcexyz);
    target_cloud =  boost::make_shared<PointCloud<PointXYZ> >(targetxyz);

    convertCloud(source_cloud, source);
    convertCloud(target_cloud, target);

    cloud_source = boost::make_shared<const PointCloud<PointNormal>>(source);
    cloud_target = boost::make_shared<const PointCloud<PointNormal>>(target);
    
    icp->setInputCloud (cloud_source);
    icp->setInputTarget (cloud_target);
        // Set the max correspondence distance to 5cm (e.g., correspondences with higher distances will be ignored)
    icp->setMaxCorrespondenceDistance (5000.0);
        // Set the maximum number of iterations (criterion 1)
    icp->setMaximumIterations (50);
        // Set the transformation epsilon (criterion 2)
    icp->setTransformationEpsilon (1e-8);
        // Set the euclidean distance difference epsilon (criterion 3)
    icp->setEuclideanFitnessEpsilon (1);
        // Perform the alignment
    PointCloud<PointNormal> cloud_source_registered;
    icp->align(cloud_source_registered);
        // Obtain the transformation that aligned cloud_source to cloud_source_registered
    Eigen::Matrix4f transformation = icp->getFinalTransformation ();
    
    std::cout << transformation << std::endl;
    std::cout << icp->getFitnessScore() << std::endl;
    
    result_cloud =  boost::make_shared<PointCloud<PointNormal> >(cloud_source_registered);
    pcl::visualization::PCLVisualizer viewer("window");
    viewer.setBackgroundColor(0, 0, 0);
    
    visualization::PointCloudColorHandlerCustom<pcl::PointNormal> final_color(result_cloud,0,255,255);
     visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> source_color(source_cloud,255,0,255);
    visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> target_color(source_cloud,255,20,255);
    
    viewer.addPointCloud<pcl::PointNormal>(result_cloud, final_color, "result");
    viewer.addPointCloud<pcl::PointXYZ>(source_cloud, source_color, "source_1");
    viewer.addPointCloud<pcl::PointXYZ>(target_cloud, target_color, "source_2");
    
    viewer.addPointCloudNormals<pcl::PointNormal, pcl::PointNormal> (result_cloud, result_cloud, 25, 0.15, "normals");
    viewer.setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "source");
    // orthographic (parallel) projection; same with pressing key 'o'
    //viewer.getRenderWindow().GetRenderers().GetFirstRenderer().GetActiveCamera().SetParallelProjection(1);
    viewer.resetCamera();
    viewer.spinOnce();
    
    while (!viewer.wasStopped()) {
        viewer.spinOnce();
    }
}


NormalsICP::~NormalsICP(){}

void NormalsICP::convertCloud(PointCloud<pcl::PointXYZ>::Ptr &source, PointCloud<PointNormal> &target){
    
    NormalEstimation<PointXYZ, PointNormal> ne;
    ne.setInputCloud(source);

    //PointCloud<PointNormal>::Ptr cloud_normals (new PointCloud<PointNormal>);

    // Use all neighbors in a sphere of radius 3cm
    ne.setRadiusSearch (3.0);

    // Compute the features
    ne.compute(target);
    
    PointCloud<PointNormal> target_out;
    
    const PointCloud<PointXYZ>      coordinates  = *source;
    const PointCloud<PointNormal>   normals      = target;
    
    concatenateFields(normals, coordinates, target);
    
    //return *cloud_normals.get();
}
