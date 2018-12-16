#include "../Headers/Register.hpp"


void Register::registration() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr buffer(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr registered(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr intermediate_points(new pcl::PointCloud<pcl::PointXYZ>);



    while (priority_points->size() < 2) {
        // idle waiting at least two point cloud
    }
    PriorityPointCloud pr = priority_points->top();
    target = pr.getPointCloud();
    priority_points->pop();
    utilities.downScale(target);
    utilities.showCloud(target);

    int k =0;

    while (!priority_points->empty()) {

        pr = priority_points->top();
        source = pr.getPointCloud();
        pcl::copyPointCloud(*source, *buffer);
        priority_points->pop();

        switch (alg) {
            case 0 :
                intermediate_points = bruteICP.bruteIcpRegistration(source, target);
                break;
            case 1 : {
                intermediate_points = normalICP.normalIcpRegistration(source, target);
                break;
            }
            default:
                break;
        }
        //counter for order the generated points useful to send message back to unity
        PriorityPointCloud generate_points =PriorityPointCloud(k,intermediate_points);
        k++;
        this->generated_points->push(generate_points);


        *registered += *intermediate_points;
        pcl::copyPointCloud(*buffer, *target);

        utilities.downScale(registered);
        utilities.refreshShowCloud(registered);

    }
    std::cout << "----END REGISTRATION----" << std::endl;
    utilities.continueShowCloud();

}

Register::Register(int alg,
                   std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
                   std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points) {
    this->generated_points = generated_points;
    this->priority_points = priority_points;
    this->alg = alg;
}

Register::~Register() {

}

Register::Register() {

}
