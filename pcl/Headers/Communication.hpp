#ifndef Communication_hpp
#define Communication_hpp

#include <zmq.hpp>
#include <vector>
#include <string>
#include <thread>

#include "Utilities.hpp"
#include "PriorityCloudComparator.hpp"
#include "Register.hpp"
#include "SettingHandler.hpp"

class Communication {

public:

    Communication();

    ~Communication();

    void establishSubscriberCommunication();

    void receiveMessage();

    void receiveSetting();

    void establishPublisherCommunication();

    void sendMessage();

    void establishSettingSubscriberCommunication();

    void startCommunication();

    void enstablishCommunication();

private:
    Utilities utilities = Utilities();

    zmq::context_t *context_sub;
    zmq::socket_t *subscriber;

    zmq::context_t *context_pub;
    zmq::socket_t *publisher;

    zmq::context_t *context_setting;
    zmq::socket_t *setting_subscriber;


    int alg = 1; // change this value to change icp algorithm
    Register *regis = nullptr;
    SettingHandler * setting_handler = nullptr;
    //std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points = nullptr;

    //point from unity
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> priority_points;
    // points already transformed and ready to be sent to unity
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> generated_points;

};

#endif /* Communication_hpp */
