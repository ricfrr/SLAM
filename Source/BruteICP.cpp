#include "../Headers/BruteICP.hpp"

BruteICP::BruteICP() {

};

BruteICP::~BruteICP() {

};

pcl::PointCloud<pcl::PointXYZ>::Ptr
BruteICP::bruteIcpRegistration(pcl::PointCloud<pcl::PointXYZ>::Ptr source, pcl::PointCloud<pcl::PointXYZ>::Ptr target) {

    utilities.downScale(source);
    utilities.downScale(target);

    pcl::PointCloud<pcl::PointXYZ>::Ptr source_trans(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::IterativeClosestPoint<pcl::PointXYZ, pcl::PointXYZ> icp;
    source_trans = source;
    icp.setInputSource(source_trans);
    icp.setInputTarget(target);
    icp.setMaximumIterations(1);
    icp.setTransformationEpsilon(1e-9);
    icp.setMaxCorrespondenceDistance(100);
    icp.setEuclideanFitnessEpsilon(1);
    icp.setRANSACOutlierRejectionThreshold(1.0);

    // increasing  k increase the precision
    int k = 0;
    do {
        icp.align(*source_trans);
        std::cout << "iteration :" << k << std::endl
                  << "The score is " << icp.getFitnessScore() << std::endl;
        k++;
    } while ((icp.getFitnessScore() >= treshold || k < 10) && k < 100);

    pcl::PointCloud<pcl::PointXYZ>::Ptr finalCloud(new pcl::PointCloud<pcl::PointXYZ>);
    finalCloud = target;
    *finalCloud += *source_trans;

    utilities.downScale(finalCloud);
    return finalCloud;
}
