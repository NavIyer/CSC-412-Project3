# pragma once

#include <iostream>
using std::string;

class Request {
public:
    string ipIn;
    string ipOut;
    int arrivalTime;
    char jobType;

    Request(int runLength);
    void Print();
};
