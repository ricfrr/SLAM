//
// Created by riccardo on 08/12/2018.
//
#include <iostream>
#include "Headers/Utilities.hpp"
#include "Headers/BruteICP.hpp"
#include "Headers/NormalICP.hpp"
#include <Eigen/Core> // Eigen matrices
#include <pcl/io/io.h>
#include <pcl/conversions.h>




int main() {
    Utilities utilities = Utilities();
    BruteICP bruteICP = BruteICP();
    NormalICP normalICP = NormalICP();

    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
	pcl::PointCloud<pcl::PointXYZ>::Ptr buffer(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr registered(new pcl::PointCloud<pcl::PointXYZ>);

    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr source_normal(new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr target_normal(new pcl::PointCloud<pcl::PointXYZRGBNormal>);
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr registerd_normal(new pcl::PointCloud<pcl::PointXYZRGBNormal>);



    utilities.loadFile("../../Points_30/(3.4, -15.1, -26.9)(0.0, 0.0, 0.0).pcd", target);
    utilities.downScale(target);
    normalICP.addNormal(target,target_normal);
    utilities.showCloud(target);
    int alg = 1; // change this value to change icp algorithm
    int directory_dimension = 360;
    for (int i = 0 ; i < directory_dimension; i++) {
            std::cout << "read : (3.4, -15.1, -26.9)(0.0, " << std::to_string(i) << ".0, 0.0).pcd" << std::endl;
            std::string filename = "../../Points_30/(3.4, -15.1, -26.9)(0.0, " + std::to_string(i) +
                                   ".0, 0.0).pcd"; // modidfy here the folder to change the dataset

            utilities.loadFile(filename, source);
            switch (alg) {
                case 0 :
					registered = bruteICP.bruteIcpRegistration(source, target);
                    break;
                case 1 :{
					pcl::copyPointCloud(*source, *buffer);
                    *registered += *normalICP.normalIcpRegistration(source,target);
					pcl::copyPointCloud(*buffer, *target);
                }
                default:
                    break;
            }
            utilities.refreshShowCloud(registered);
    }
    utilities.downScale(registerd_normal);
    utilities.saveFile(registerd_normal);
    utilities.continueShowCloud();
    return 0;
}