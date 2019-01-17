#include "../Headers/BruteICP.hpp"

BruteICP::BruteICP() {
    pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB>::Ptr icp(new pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB>());
    icp->setMaximumIterations(100);
    icp->setTransformationEpsilon(1e-9);
    icp->setMaxCorrespondenceDistance(100);
    icp->setEuclideanFitnessEpsilon(1e-9);
    this->icp = icp;
};

BruteICP::~BruteICP() {

};

pcl::PointCloud<pcl::PointXYZRGB>::Ptr
BruteICP::bruteIcpRegistration(pcl::PointCloud<pcl::PointXYZRGB>::Ptr source, pcl::PointCloud<pcl::PointXYZRGB>::Ptr target) {

    utilities.downScale(source);
    utilities.downScale(target);

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr source_trans(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::copyPointCloud(*source,*source_trans);
    icp->setInputSource(source_trans);
    icp->setInputTarget(target);

    icp->align(*source_trans);

    *transformation *= icp->getFinalTransformation();
    if (icp->hasConverged()) {
        pcl::transformPointCloud(*source, *source, *transformation);
        //std::cout << "score : " << icp->getFitnessScore() << std::endl;
    } else {
        std::cerr << "DIVERGED" << std::endl;
    }
    //std::cout << "local " << std::endl << icp->getFinalTransformation() << std::endl;
    //std::cout << "global " << std::endl << transformation << std::endl;

    return source;
}

pcl::IterativeClosestPoint<pcl::PointXYZRGB, pcl::PointXYZRGB>::Ptr BruteICP::getICP(){
    return icp;
}

void BruteICP::resetTransformationMatrix() {
    //this->transformation = Eigen::Matrix4f::Identity();
}

void BruteICP::setTransformationMatrix(Eigen::Matrix4f * _transformation){
    this->transformation = _transformation;
}

