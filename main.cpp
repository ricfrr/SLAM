//
// Created by riccardo on 08/12/2018.
//
#include <iostream>
#include "Headers/Utilities.hpp"
#include "Headers/BruteICP.hpp"
#include "Headers/NormalICP.hpp"



int main() {
    Utilities utilities = Utilities();
    BruteICP bruteICP = BruteICP();
    NormalICP normalICP = NormalICP();

    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr registerd(new pcl::PointCloud<pcl::PointXYZ>);


    utilities.loadFile("../Points_30/(3.4, -15.1, -26.9)(0.0, 0.0, 0.0).pcd", target);

    utilities.showCloud(target);
    int alg = 1; // change this value to change icp algorithm
    int directory_dimension = 10;
    for (int i = 0 ; i < directory_dimension; i++) {
            std::cout << "read : (3.4, -15.1, -26.9)(0.0, " << std::to_string(i) << ".0, 0.0).pcd" << std::endl;
            std::string filename = "../Points_30/(3.4, -15.1, -26.9)(0.0, " + std::to_string(i) +
                                   ".0, 0.0).pcd"; // modidfy here the folder to change the dataset

            utilities.loadFile(filename, source);
            switch (alg) {
                case 0 :
                    registerd = bruteICP.bruteIcpRegistration(source, target);
                    break;
                case 1 :
                    registerd = normalICP.normalIcpRegistration(source,target);
                default:
                    break;
            }
            utilities.refreshShowCloud(registerd);
            target = registerd;
    }

    utilities.saveFile(registerd);
    utilities.continueShowCloud();
    return 0;
}