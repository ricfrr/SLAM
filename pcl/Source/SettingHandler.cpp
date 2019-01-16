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
    if (msg == "ITERATION") {
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setMaximumIterations(setting->getValue());
        } else if (regis->getAlgorithm() == 1) {
            NormalICP *nr = regis->getNormalICP();
            nr->getICP()->setMaximumIterations(setting->getValue());
        }
    }
    if (msg== "ALGORITHM") {
        regis->setAlgorithm(setting->getValue());
        std::cout << "algorithm changed in: " << regis->getAlgorithm() << std::endl;
    }
    if (msg == "CORRESPONDENCE") {
        if (regis->getAlgorithm() == 0) {
            BruteICP *br = regis->getBruteICP();
            br->getICP()->setMaxCorrespondenceDistance(setting->getValue());
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