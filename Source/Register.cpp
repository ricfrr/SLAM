#include "../Headers/Register.hpp"


void Register::registration(){
    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr buffer(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr registered(new pcl::PointCloud<pcl::PointXYZ>);
    while(priority_points->size()<2){
        // idle waiting at least two point cloud
    }
    PriorityPointCloud pr  = priority_points->top();
    target = pr.getPointCloud();
    priority_points->pop();
    utilities.downScale(target);
    utilities.showCloud(target);
    while(!priority_points->empty()){

        pr = priority_points->top();
        source = pr.getPointCloud();
        pcl::copyPointCloud(*source, *buffer);
        priority_points->pop();

        switch (alg) {
            case 0 :
                *registered += *bruteICP.bruteIcpRegistration(source, target);
                break;
            case 1 : {
                *registered += *normalICP.normalIcpRegistration(source, target);
                break;
            }
            default:
                break;
        }
        pcl::copyPointCloud(*buffer, *target);

        utilities.downScale(registered);
        utilities.refreshShowCloud(registered);
    }
    std::cout<<"----END REGISTRATION----"<<std::endl;
    utilities.continueShowCloud();

}

Register::Register(int alg,
                   std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator>*  priority_points) {

    this->priority_points = priority_points;
    this->alg = alg;
}

Register::~Register() {

}

Register::Register() {

}
