#include "../Headers/Communication.hpp"


Communication::Communication() {
    context_sub = new zmq::context_t(1);
    subscriber = new zmq::socket_t(*context_sub, ZMQ_SUB);

    context_pub = new zmq::context_t(1);
    publisher = new zmq::socket_t(*context_pub, ZMQ_PUB);

    context_setting = new zmq::context_t(1);
    setting_subscriber = new zmq::socket_t(*context_setting,ZMQ_SUB);

    this->regis = new Register(&priority_points,&generated_points);
    this->setting_handler = new SettingHandler(&priority_points,&generated_points,this->regis);
}

Communication::~Communication() {

};

void Communication::establishSettingSubscriberCommunication() {
    setting_subscriber->connect("tcp://127.0.0.1:12348");
    setting_subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);
}

void Communication::establishSubscriberCommunication() {
    subscriber->connect("tcp://127.0.0.1:12347");
    subscriber->setsockopt(ZMQ_SUBSCRIBE, "", 0);
};

void Communication::establishPublisherCommunication() {
    publisher->bind("tcp://127.0.0.1:12346");
}

std::string generateMessage(PriorityPointCloud &cloud) {
    pcl::PointCloud<pcl::PointXYZ>::Ptr tmp_cloud = cloud.getPointCloud();
    int priority = cloud.getPriority();
    std::string message = std::to_string(priority) + "\n";

    for (size_t i = 0; i < tmp_cloud->points.size(); ++i) {
        message += std::to_string(tmp_cloud->points[i].x) + " " + std::to_string(tmp_cloud->points[i].y) + " " +
                   std::to_string(tmp_cloud->points[i].z) + "\n";
    }
    return message;
}

void Communication::sendMessage() {
    while (true) {
        if (!this->generated_points.empty()) {

            PriorityPointCloud gen_cloud = this->generated_points.top();
            std::string message = generateMessage(gen_cloud);

            this->generated_points.pop();
            zmq::message_t cloud(message.length());
            memcpy(cloud.data(), message.c_str(), message.length());
            this->publisher->send(cloud);

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void Communication::receiveMessage() {
    do {
        zmq::message_t request;
        subscriber->recv(&request);
        std::string points = std::string(static_cast<char *>(request.data()), request.size());
        PriorityPointCloud pr = utilities.fromStringToPriorityPointCloud(points);
        priority_points.push(pr);
    }while(true);
}

void Communication::receiveSetting() {
    do {
        zmq::message_t request;
        setting_subscriber->recv(&request);
        std::cout << "setting received" << std::endl;
        std::string setting = std::string(static_cast<char *>(request.data()), request.size());
        Setting* st = utilities.fromStringToSetting(setting);
        setting_handler->handleSetting(st);
    }while(true);
}

void Communication::startCommunication(){

    std::thread receive_thread(&Communication::receiveMessage, this);
    std::thread registration_thread (&Register::registration,this->regis);
    std::thread send_thread (&Communication::sendMessage, this);
    std::thread setting(&Communication::receiveSetting, this);

    std::cout<<"PRESS q to close the program"<<std::endl;
    std::string c;
    do{
        std::cin>>c;
    }while (c!="q");
}

void Communication::enstablishCommunication() {
    this->establishSubscriberCommunication();
    this->establishSettingSubscriberCommunication();
    this->establishPublisherCommunication();
}




