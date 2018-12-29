#include "../Headers/Setting.hpp"

Setting::Setting(std::string _message){
    this->message = _message;
};
Setting::Setting(std::string _message, float value){
    this->message = _message;
    this->value = value;
};

Setting::~Setting(){

};

std::string Setting::getMessage(){
    return message;
};
float Setting::getValue(){
    return value;
};