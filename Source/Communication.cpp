#include "../Headers/Communication.hpp"

Communication::Communication(
        std::priority_queue <PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *points) {
    context_sub = new zmq::context_t(1);
    subscriber = new zmq::socket_t(*context_sub, ZMQ_SUB);

    context_pub = new zmq::context_t(1);
    publisher = new zmq::socket_t(*context_pub, ZMQ_PUB);

    generated_points = points;
};

Communication::~Communication() {

};


void Communication::enstablishSubscriberCommunication() {
    subscriber->connect("tcp://127.0.0.1:12347");
    subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);
};

void Communication::enstablishPublisherComunication() {
    publisher->bind("tcp://127.0.0.1:12346");
}

std::string generateMessage(PriorityPointCloud &cloud) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr tmp_cloud = cloud.getPointCloud();
    int priority = cloud.getPriority();
    std::string message = std::to_string(priority) + "\n";

    for (size_t i = 0; i < tmp_cloud->points.size(); ++i) {
        message += std::to_string(tmp_cloud->points[i].x) + " " + std::to_string(tmp_cloud->points[i].y) + " " + std::to_string(tmp_cloud->points[i].z) + "\n";
    }
    return message;
}

void Communication::sendMessage() {
    while (true) {
        if (!this->generated_points->empty()) {

            PriorityPointCloud gen_cloud = this->generated_points->top();
            std::string message = generateMessage(gen_cloud);

            this->generated_points->pop();
            zmq::message_t cloud(message.length());
            memcpy(cloud.data(), message.c_str(), message.length());
            this->publisher->send(cloud);

            std::cout << "sent!" << std::endl;
        }
    }
}

std::string Communication::receiveMessage() {
    std::cout << "waiting" << std::endl;
    zmq::message_t request;
    subscriber->recv(&request);
    std::string points = std::string(static_cast<char *>(request.data()), request.size());
    return points;
}