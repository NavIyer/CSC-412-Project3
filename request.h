# pragma once

#include <iostream>
#include "utils.h"
using std::string;
using std::cout;
using std::endl;

class Request {
public:
    string ipIn;
    string ipOut;
    int processingTime;
    char jobType;

    Request(int maxProcessingTime);
    void Print();
};

