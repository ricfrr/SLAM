#include "../Headers/Utilities.hpp"


Utilities::Utilities() {

};

Utilities::~Utilities() {

};


std::vector<std::string> Utilities::split(const std::string &str, const std::string &delim) {
    std::vector<std::string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == std::string::npos) pos = str.length();
        std::string token = str.substr(prev, pos - prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}



PriorityPointCloud Utilities::fromStringToPriorityPointCloud(const std::string &st) {

    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZRGB>);
    std::vector<std::string> lines = split(st, "\n");
    // priority of the point cloud
    int priority = std::stoi(lines[0]);
    //generate the point cloud
    for (int i = 1; i < lines.size(); i++) {
        std::vector<std::string> point = split(lines[i]," ");
        pcl::PointXYZRGB point_xyz_rgb = pcl::PointXYZRGB(); //point xyzrgb
        point_xyz_rgb.x = std::stof(point[0]);
        point_xyz_rgb.y= std::stof(point[1]);
        point_xyz_rgb.z = std::stof(point[2]);
        point_xyz_rgb.r = std::stof(point[3]);
        point_xyz_rgb.g = std::stof(point[4]);
        point_xyz_rgb.b = std::stof(point[5]);

        //pcl::PointXYZRGB t_point = pcl::PointXYZRGB(std::stof(point[0]),std::stof(point[1]),std::stof(point[2]));
        cloud->push_back(point_xyz_rgb);
    }
    //generate the priority point cloud
    PriorityPointCloud priorityPointCloud = PriorityPointCloud(priority,cloud);
    // push the priority point cloud to the queue
    return priorityPointCloud;
}


void Utilities::loadFile(const std::string fileName, pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {
    pcl::io::loadPCDFile<pcl::PointXYZRGB> (fileName, *cloud);
    Eigen::Matrix4f mirrorX; // Mirror over x-axis. Unity is left-handed, whilst PCL is right-handed
    mirrorX << -1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;
    pcl::transformPointCloud(*cloud, *cloud, mirrorX);

}

void Utilities::saveFile(pcl::PointCloud<pcl::PointXYZRGB>::Ptr &cloud) {
    pcl::io::savePCDFileASCII("../final_cloud.pcd", *cloud);

}

void Utilities::saveFile(pcl::PointCloud<pcl::PointXYZRGBNormal>::Ptr &cloud) {
    pcl::io::savePCDFileASCII("../final_cloud.pcd", *cloud);

}

void Utilities::showCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {

    boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
    viewer->setBackgroundColor(0, 0, 0);

    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> final_color(cloud, 0, 255, 0);
    viewer->addPointCloud<pcl::PointXYZRGB>(cloud, final_color, "source");
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

void Utilities::refreshShowCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color(cloud, 0, 255, 0);
    viewer->updatePointCloud(cloud, cloud_color, "source");
    viewer->spinOnce();
};

/*void Utilities::refreshShowCloud(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {
    pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZRGB> cloud_color(cloud, 0, 255, 0);
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

void Utilities::downScale(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud) {
    sor.setInputCloud(cloud);
    sor.setLeafSize(1.0f, 1.0f, 1.0f);
    sor.filter(*cloud);
};

void Utilities::continueShowCloud() {
    while (!viewer->wasStopped()) {
        viewer->spinOnce();
    }
}

void Utilities::transform(pcl::PointCloud<pcl::PointXYZRGB>::Ptr source){
    Eigen::Affine3f transform = Eigen::Affine3f::Identity();
    transform.translation() << 0.0, 0.0, 0.0;
    double theta = 2.0*M_PI/360.0;
    transform.rotate (Eigen::AngleAxisf (theta, Eigen::Vector3f::UnitY()));
    pcl::transformPointCloud (*source, *source, transform);
}

Setting* Utilities::fromStringToSetting(const std::string &st) {
    std::vector<std::string> lines = split(st, "\n");
    Setting* setting = nullptr;
    std::string first_param = lines[0];
    float second_param;
    if(lines.size()>1){
        second_param = std::stof(lines[1]);
        setting = new Setting(first_param,second_param);
        //std::cout << setting->getMessage()<<" "<<setting->getValue()<<std::endl;
    }else{
        setting = new Setting(first_param);
        //std::cout << setting->getMessage()<<std::endl;
    }

    return setting;
}

