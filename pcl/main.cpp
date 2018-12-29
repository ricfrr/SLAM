//
// Created by riccardo on 08/12/2018.
//
#include <iostream>
#include "Headers/Communication.hpp"

int main() {

    Communication communication = Communication();
    communication.enstablishCommunication();
    communication.startCommunication();

    return 0;
}