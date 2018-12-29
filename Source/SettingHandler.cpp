#include "../Headers/SettingHandler.hpp"

SettingHandler::SettingHandler(
        std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
        std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points, Register * regis) {
    this->generated_points = generated_points;
    this->priority_points = priority_points;
    this->regis = regis;
}


void SettingHandler::handleSetting(Setting * setting){
    std::string msg = setting->getMessage();
    if(msg == "RESET"){
        resetPriorityPoints();
    }
};

void SettingHandler::resetPriorityPoints(){
    while (priority_points->size()!=0){
        priority_points->pop();
    }
    this->regis->resetRegisteredPoint();

    std::cout<<"------------------------RESET---------------------------------"<<std::endl;
};