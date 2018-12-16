#ifndef Communication_hpp
#define Communication_hpp

#include <zmq.hpp>
#include <vector>
#include <string>

#include "Utilities.hpp"
#include "PriorityCloudComparator.hpp"

class Communication {

public:
    Communication(
            std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *points);

    Communication();

    ~Communication();

    void enstablishSubscriberCommunication();

    std::string receiveMessage();

    void enstablishPublisherComunication();

    void sendMessage();

private:
    zmq::context_t *context_sub;
    zmq::socket_t *subscriber;

    zmq::context_t *context_pub;
    zmq::socket_t *publisher;

    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points = nullptr;

};

#endif /* Communication_hpp */
