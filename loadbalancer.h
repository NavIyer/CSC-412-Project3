#pragma once

#include <iostream>
#include <queue>
#include <vector>
#include <tuple>
#include <algorithm>
#include "request.h"
#include "webserver.h"

using std::vector;
using std::string;
using std::queue;
using std::cout;
using std::endl;
using std::pair;
using std::sort;

class LoadBalancer {
public:
    vector<WebServer> servers;
    queue<Request> requestQueue;

    int currentTime;
    int requestsProcessed;
    int requestsDropped;
    int requestsCompleted;
    int maxQueueSize;

    LoadBalancer(int numServers, int deactivateTimeout, int maxQueueSize);
    void EnqueueRequests(vector<Request> requests);
    void Tick();
    int NumActiveServers();
    int NumFreeServers();
    void Print();
};
