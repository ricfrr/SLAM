#ifndef SettingHandler_hpp
#define SettingHandler_hpp

#include <vector>
#include <string>

#include "Register.hpp"
#include "Setting.hpp"

class SettingHandler{

public:
    SettingHandler();

    SettingHandler(std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points,
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points, Register * regis);

    ~SettingHandler();

    void handleSetting(Setting * setting);
    void resetPriorityPoints();

private:
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *priority_points = nullptr;
    std::priority_queue<PriorityPointCloud, std::vector<PriorityPointCloud>, PriorityCloudComparator> *generated_points = nullptr;
    Register * regis = nullptr;

};

#endif /* SettingHandler_hpp */
