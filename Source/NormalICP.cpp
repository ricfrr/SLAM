#include "../Headers/NormalICP.hpp"

NormalICP::NormalICP(){

};

NormalICP::~NormalICP(){

};


void NormalICP::addNormal(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_with_normals) {

    pcl::PointCloud<pcl::Normal>::Ptr normals(new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr searchTree(new pcl::search::KdTree<pcl::PointXYZ>);
    searchTree->setInputCloud(cloud);
    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> normalEstimator;
    normalEstimator.setInputCloud(cloud);
    normalEstimator.setSearchMethod(searchTree);
    normalEstimator.setKSearch(15);
    normalEstimator.compute(*normals);
    pcl::concatenateFields(*cloud, *normals, *cloud_with_normals);

}

pcl::PointCloud<pcl::PointXYZ>::Ptr NormalICP::normalIcpRegistration(pcl::PointCloud<pcl::PointXYZ>::Ptr source, pcl::PointCloud<pcl::PointXYZ>::Ptr target){
    utilities.downScale(source);
    utilities.downScale(target);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_source_trans(new pcl::PointCloud<pcl::PointXYZ>());
    cloud_source_trans = source;

    // prepare could with normals
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_source_normals(
            new pcl::PointCloud<pcl::PointXYZRGBNormal>());
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_target_normals(
            new pcl::PointCloud<pcl::PointXYZRGBNormal>());
    pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud_source_trans_normals(
            new pcl::PointCloud<pcl::PointXYZRGBNormal>());

    addNormal(source, cloud_source_normals);
    addNormal(target, cloud_target_normals);
    addNormal(cloud_source_trans, cloud_source_trans_normals);

    pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>::Ptr icp(
            new pcl::IterativeClosestPointWithNormals<pcl::PointXYZRGBNormal, pcl::PointXYZRGBNormal>());
    icp->setMaximumIterations(1);
    icp->setInputSource(cloud_source_trans_normals); // not cloud_source, but cloud_source_trans!
    icp->setInputTarget(cloud_target_normals);
    int k = 0;
    do {
        icp->align(*cloud_source_trans_normals);
        if (icp->hasConverged()){
            pcl::transformPointCloud(*source, *cloud_source_trans, icp->getFinalTransformation());
            std::cout << "score : " << icp->getFitnessScore() << std::endl;
        }else{
            std::cerr<<"DIVERGED"<<std::endl;
            break;
        }
        k++;
    } while((icp->getFitnessScore()>=0.3 || k<7) && (k<100));

    std::cout<<"done "<<k<<" align"<<std::endl;

    pcl::PointCloud<pcl::PointXYZ>::Ptr final_cloud(new pcl::PointCloud<pcl::PointXYZ>());


    if(icp->hasConverged()){
        *final_cloud = *target;
        *final_cloud += *cloud_source_trans;
    }

    utilities.downScale(final_cloud);
    return  final_cloud;

};