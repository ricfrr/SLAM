#ifndef Noise_hpp
#define Noise_hpp

#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <map>
#include <string>

#include "Utilities.hpp"

class Noise{
    public:
        Noise();
        Noise(int percentage);

        ~Noise();

        void addNoise(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudToModify);
    
    private:
        int percentage;
        //Const for the gaussians distribution
        const double mean = 0.0;
        const double inclination = 0.1/5.8; //Using data from a real TOF camera and needed to give a correct sigma from the distance
};

#endif //Noise_hpp