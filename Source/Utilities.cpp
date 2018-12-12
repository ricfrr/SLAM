#include "../Headers/Utilities.hpp"


Utilities::Utilities() {

};

Utilities::~Utilities() {

};

void Utilities::loadFile(const std::string fileName, pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    pcl::io::loadPCDFile<pcl::PointXYZ> (fileName, *cloud);
   // Eigen::Matrix4f mirrorX; // Mirror over x-axis. Unity is left-handed, whilst PCL is right-handed
    //mirrorX << -1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;
    //pcl::transformPointCloud(*cloud, *cloud, mirrorX);

    /*
    pcl::PolygonMesh mesh;
    if (pcl::io::loadPolygonFile(fileName, mesh) == -1) {
        PCL_ERROR ("loadFile fail.");
        return;
    }
    pcl::fromPCLPointCloud2<pcl::PointXYZ>(mesh.cloud, *cloud);
    // remove points having values of nan
    std::vector<int> index;
    pcl::removeNaNFromPointCloud(*cloud, *cloud, index);*/
}

void Utilities::saveFile(pcl::PointCloud<pcl::PointXYZ>::Ptr &cloud) {
    pcl::io::savePCDFileASCII("../final_cloud.pcd", *cloud);

}

void Utilities::saveFile(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr &cloud) {
    pcl::io::savePCDFileASCII("../final_cloud.pcd", *cloud);

}

void Utilities::showCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> final_color(cloud, 0, 255, 0);
    viewer->addPointCloud<pcl::PointXYZ>(cloud, final_color, "source");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "source");
    // orthographic (parallel) projection; same with pressing key 'o'
    viewer->getRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->SetParallelProjection(1);
    viewer->resetCamera();
    viewer->spinOnce();
    this->viewer = viewer;

};

void Utilities::showCloud(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud) {

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGBNormal> final_color(cloud, 0, 255, 0);
    viewer->addPointCloud<pcl::PointXYZRGBNormal>(cloud, final_color, "source");
    viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 1, "source");
    // orthographic (parallel) projection; same with pressing key 'o'
    viewer->getRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActiveCamera()->SetParallelProjection(1);
    viewer->resetCamera();
    viewer->spinOnce();
    this->viewer = viewer;

};

void Utilities::refreshShowCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloud, 0, 255, 0);
    viewer->updatePointCloud(cloud, cloud_color, "source");
    viewer->spinOnce();
};

/*void Utilities::refreshShowCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloud, 0, 255, 0);
    viewer->updatePointCloud(cloud, cloud_color, "source");
    viewer->spinOnce();
};*/

void Utilities::refreshShowCloud(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud) {
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGBNormal> cloud_color(cloud, 0, 255, 0);
    viewer->updatePointCloud(cloud, cloud_color, "source");
    viewer->spinOnce();
};



void Utilities::downScale(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr cloud) {
    sor_normal.setInputCloud(cloud);
    sor_normal.setLeafSize(1.0f, 1.0f, 1.0f);
    sor_normal.filter(*cloud);
};

void Utilities::downScale(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    sor.setInputCloud(cloud);
    sor.setLeafSize(1.0f, 1.0f, 1.0f);
    sor.filter(*cloud);
};

void Utilities::continueShowCloud() {
    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }
}

void Utilities::transform(pcl::PointCloud<pcl::PointXYZ>::Ptr source){
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translation() << 0.0, 0.0, 0.0;
    double theta = 2.0*M_PI/360.0;
    transform.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitY()));
    pcl::transformPointCloud (*source, *source, transform);
}

