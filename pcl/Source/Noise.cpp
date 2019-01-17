#include "../Headers/Noise.hpp"


Noise::Noise(){
    percentage=1;
};
Noise::~Noise(){
};
Noise::Noise(int percent){
    percentage = percent/100;
};

void Noise::addNoise(pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloudToModify){
    std::mt19937 generatorDistance(std::random_device{}());
    std::mt19937 generatorReflection(std::random_device{}());

    for(auto& x : cloudToModify->points){
        //Standard deviation given by the distance as factor of inclination
        float stddev = x.z*inclination;
        float reflection = 0.5;
        //Generating the normal distribution for the errors
        std::normal_distribution<float> dist(mean, stddev); //Distribution for distances
        std::normal_distribution<float> rifl(mean, reflection);
        //Generetaing the errors
        float ErrDist= dist(generatorDistance);
        float ErrRefl= rifl(generatorReflection);
        x.z += (ErrDist+ErrRefl)*percentage;
    }
}