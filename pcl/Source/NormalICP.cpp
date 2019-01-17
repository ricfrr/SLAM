#include "../Headers/NormalICP.hpp"

NormalICP::NormalICP() {
	pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>::Ptr icp(
		new pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>());
	icp->setMaximumIterations(10);
	icp->setTransformationEpsilon(1e-9);
	icp->setEuclideanFitnessEpsilon(1e-9);
	this->icp = icp;
};

NormalICP::~NormalICP() {

};


void NormalICP::addNormal(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud,
                          pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals) {

    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZRGB>::Ptr searchTree(new pcl::search::KdTree<pcl::PointXYZRGB>);
    searchTree->setInputCloud(cloud);
    pcl::NormalEstimation<pcl::PointXYZRGB, pcl::Normal> normalEstimator;
    normalEstimator.setInputCloud(cloud);
    normalEstimator.setSearchMethod(searchTree);
    normalEstimator.setKSearch(20);
    normalEstimator.compute(*normals);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);

}

pcl::PointCloud<pcl::PointXYZRGB>::Ptr
NormalICP::normalIcpRegistration(pcl::PointCloud<pcl::PointXYZRGB>::Ptr source,
                                 pcl::PointCloud<pcl::PointXYZRGB>::Ptr target) {

    utilities.downScale(source);
	utilities.downScale(target);
    // prepare could with normals
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_source_normals(
            new pcl::PointCloud<pcl::PointXYZRGBNormal>());
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_target_normals(
            new pcl::PointCloud<pcl::PointXYZRGBNormal>());

    addNormal(source, cloud_source_normals);
    addNormal(target, cloud_target_normals);


    icp->setInputSource(cloud_source_normals);
    icp->setInputTarget(cloud_target_normals);
    icp->align(*cloud_source_normals);

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
};

pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>::Ptr NormalICP::getICP(){
    return icp;
}

void NormalICP::resetTransformationMatrix() {
    //this->transformation = Eigen::Matrix4f::Identity();
}

void NormalICP::setTransformationMatrix(Eigen::Matrix4f * _transformation) {
    this->transformation = _transformation;
}
