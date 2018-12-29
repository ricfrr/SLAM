#ifndef Setting_hpp
#define Setting_hpp

#include <vector>
#include <string>


class Setting {

public:
    Setting(std::string _message);

    Setting(std::string _message, float value);

    ~Setting();

    std::string getMessage();
    float getValue();
private:
    std::string message;
    float value;
};

#endif /* Setting_hpp */
