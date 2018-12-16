//
// Created by riccardo on 08/12/2018.
//
#include <iostream>
#include <fstream>
#include "Headers/Utilities.hpp"
#include "Headers/Register.hpp"
#include "Headers/PriorityPointCloud.hpp"
#include "Headers/PriorityCloudComparator.hpp"
#include "Headers/Communication.hpp"
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

    //point from unity
    std::priority_queue<PriorityPointCloud , std::vector<PriorityPointCloud >, PriorityCloudComparator> priority_points;
    // points already transformed and ready to be sent to unity
    std::priority_queue<PriorityPointCloud , std::vector<PriorityPointCloud >, PriorityCloudComparator> generated_points;

    Utilities utilities;
    Communication communication = Communication(&generated_points);
    // connection with Unity
    communication.enstablishSubscriberCommunication();
    communication.enstablishPublisherComunication();

    int alg = 1; // change this value to change icp algorithm
    Register regis = Register(alg,&priority_points,&generated_points);

    std::thread registration_thread (&Register::registration,&regis);
    std::thread send_thread (&Communication::sendMessage, &communication);
    do {
        std::string pc = communication.receiveMessage();
        PriorityPointCloud pr = utilities.fromStringToPriorityPointCloud(pc);
        priority_points.push(pr);
    } while (!priority_points.empty());

    std::cout<<"----NO MORE POINTS RECEIVED-----"<<std::endl;


    return 0;
}