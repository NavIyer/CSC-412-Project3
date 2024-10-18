#pragma once

#include <iostream>
#include "request.h"
using std::string;
using std::cout;
using std::endl;

class WebServer {
public:
    int freeAtTime;  // Time when server will be free
    int deactivateTimeout;  // Time to deactivate server after last request

    WebServer(int deactivateTimeout);
    void ProcessRequest(Request request, int currentTime);
    bool IsFree(int currentTime);
    bool IsActivated(int currentTime);
    void Print(int currentTime);
};

