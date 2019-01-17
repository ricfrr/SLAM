#include "../Headers/Register.hpp"


pcl::PointCloud<pcl::PointXYZ>::Ptr Register::getRegisteredPoints(){
    return registered;
}

void Register::registration() {
    std::cout<<"REGISTRATION"<<std::endl;
    pcl::PointCloud<pcl::PointXYZ>::Ptr source(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr target(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr buffer(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PointCloud<pcl::PointXYZ>::Ptr tm_registered(new pcl::PointCloud<pcl::PointXYZ>);
    this->registered = tm_registered;
    pcl::PointCloud<pcl::PointXYZ>::Ptr intermediate_points(new pcl::PointCloud<pcl::PointXYZ>);


    while (priority_points->size() < 2) {
        // idle waiting at least two point cloud
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    std::cout<<"out of loop"<<priority_points->size()<<std::endl;
    PriorityPointCloud pr = priority_points->top();
    target = pr.getPointCloud();
    priority_points->pop();
    utilities.downScale(target);
    utilities.showCloud(target);

    int k = 0;

    while (true) {
        if (!priority_points->empty()) {
            //std::cout<<"REGISTRATION LOOP "<<priority_points->size()<<std::endl;

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
            PriorityPointCloud generate_points = PriorityPointCloud(k, intermediate_points);
            k++;
            this->generated_points->push(generate_points);


            *registered += *intermediate_points;
            pcl::copyPointCloud(*buffer, *target);

            utilities.downScale(registered);
            utilities.refreshShowCloud(registered);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
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
    this->normalICP.setTransformationMatrix(&this->transformation);
    this->bruteICP.setTransformationMatrix(&this->transformation);

}
Register::Register(std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
                   std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points) {
    this->generated_points = generated_points;
    this->priority_points = priority_points;
    this->alg = 1;
    this->normalICP.setTransformationMatrix(&this->transformation);
    this->bruteICP.setTransformationMatrix(&this->transformation);
    std::cout<<"INITIALIZATION REGISTER"<<std::endl;
}

Register::~Register() {

}

Register::Register() {

}

BruteICP *Register::getBruteICP() {
    return &bruteICP;
}

NormalICP *Register::getNormalICP() {
    return &normalICP;
}

void Register::resetRegisteredPoint() {
    pcl::PointCloud<pcl::PointXYZ>::Ptr tm_registered(new pcl::PointCloud<pcl::PointXYZ>);
    this->registered =tm_registered;
    this->transformation = Eigen::Matrix4f::Identity();//TODO check this value
    bruteICP.setTransformationMatrix(&this->transformation);
    normalICP.setTransformationMatrix(&this->transformation);
}

int Register::getAlgorithm() {
    return this->alg;
}

void Register::setAlgorithm(int _alg) {
    this->alg = _alg;
}
