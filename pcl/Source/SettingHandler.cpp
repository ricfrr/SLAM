#include "../Headers/SettingHandler.hpp"

SettingHandler::SettingHandler(
        std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
        std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points,
        Register *regis) {
    this->generated_points = generated_points;
    this->priority_points = priority_points;
    this->regis = regis;
}


void SettingHandler::handleSetting(Setting *setting) {
    std::string msg = setting->getMessage();
    if (msg == "RESET") {
        resetPriorityPoints();
    }
    if (msg == "NOISE") {
        regis->setNoiseValue((regis->getNoiseValue()+1)%2);
        std::cout<<"Noise changed in: "<<regis->getNoiseValue()<<std::endl;
    }
    if (msg == "ITERATION") {
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setMaximumIterations(setting->getValue());
        } else if (regis->getAlgorithm() == 1) {
            NormalICP *nr = regis->getNormalICP();
            nr->getICP()->setMaximumIterations(setting->getValue());
        }
        std::cout<<"iteration setted to : "<<setting->getValue()<<std::endl;
    }
    if (msg== "ALGORITHM") {
        regis->setAlgorithm(setting->getValue());
        std::cout << "algorithm changed in: " << regis->getAlgorithm() << std::endl;
    }
    if (msg == "CORRESPONDENCE") {
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setMaxCorrespondenceDistance(setting->getValue());
            std::cout << "correspondece setted at: " << setting->getValue()<< std::endl;

        }
    }
    if (msg == "EUCLIDEAN_FITNESS") {
        double fitness = 1*(pow(10.0,-1*setting->getValue()));
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setEuclideanFitnessEpsilon(fitness);
            std::cout << "euclidean fitness setted at : 1e-" << setting->getValue()<< std::endl;
        }
        if (regis->getAlgorithm() == 1) {
            NormalICP *nr = regis->getNormalICP();
            nr->getICP()->setEuclideanFitnessEpsilon(fitness);
            std::cout << "euclidean fitness setted at : 1e-" << setting->getValue()<< std::endl;
        }
    }

    if (msg == "TRANSFORMATION_EPSILON") {
        double fitness = 1*(pow(10.0,-1*setting->getValue()));
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setTransformationEpsilon(fitness);
            std::cout << "transformation epsilon setted at : 1e-" << setting->getValue()<< std::endl;
        }
        if (regis->getAlgorithm() == 1) {
            NormalICP *nr = regis->getNormalICP();
            nr->getICP()->setTransformationEpsilon(fitness);
            std::cout << "transformation epsilon setted at : 1e-" << setting->getValue()<< std::endl;
        }
    }


};

void SettingHandler::resetPriorityPoints() {
    while (priority_points->size() != 0) {
        priority_points->pop();
    }
    this->regis->resetRegisteredPoint();

    std::cout << "------------------------RESET---------------------------------" << std::endl;
};