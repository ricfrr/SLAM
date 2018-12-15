//
// Created by riccardo on 08/12/2018.
//
#include <iostream>
#include <fstream>
#include "Headers/Utilities.hpp"
#include "Headers/Register.hpp"
#include "Headers/PriorityPointCloud.hpp"
#include "Headers/PriorityCloudComparator.hpp"
#include <Eigen/Core>// Eigen matrices
#include <pcl/io/io.h>
#include <pcl/common/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/conversions.h>
#include <zmq.hpp>
#include <chrono>
#include <boost/thread.hpp>
#include <thread>
#include <zconf.h>
#include <queue>


int main() {
    Utilities utilities;

    // connection with the Unity
    zmq::context_t context(1);
    zmq::socket_t subscriber(context, ZMQ_SUB);
    subscriber.connect("tcp://127.0.0.1:12347");
    subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    std::priority_queue<PriorityPointCloud , std::vector<PriorityPointCloud >, PriorityCloudComparator> priority_points;
    int alg = 1; // change this value to change icp algorithm
    Register regis = Register(alg,&priority_points);

    bool initial_point_cloud = true;
    std::thread registration_thread (&Register::registration,&regis);
    do {
        std::cout << "waiting" << std::endl;
        zmq::message_t request;
        subscriber.recv(&request);
        std::string pc = std::string(static_cast<char *>(request.data()), request.size());
        PriorityPointCloud pr = utilities.fromStringToPriorityPointCloud(pc);
        priority_points.push(pr);
        // run the registration in a different thread
    } while (!priority_points.empty());

    std::cout<<"----NO MORE POINTS RECEIVED-----"<<std::endl;


/*  FUNCTION FOR SENDIND MESSAGES
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_PUB);
    socket.bind ("tcp://127.0.0.1:12345");
    while (true) {

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply);
        std::cout<<"sent!"<<std::endl;
    }
*/

    return 0;
}