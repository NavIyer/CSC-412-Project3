#pragma once

#include <iostream>
#include "request.h"
using std::string;
using std::cout;
using std::endl;

/**
 * @brief Web server class for processing requests
 * 
 * The WebServer class represents a single web server in the load balancer system. It keeps track of when the server will be free to process a new request, and when it should be deactivated after processing a request.
 * 
 */
class WebServer {
public:
    /**
     * @brief Time when the server will be free
     * 
     * The freeAtTime variable represents the time when the server will be free to process a new request. If the current time is greater than or equal to freeAtTime, the server is considered free.
     * 
     */
    int freeAtTime;

    /**
     * @brief Time to deactivate server after last request
     * 
     * The deactivateTimeout variable represents the time to deactivate the server after processing a request. If the server has been free for longer than deactivateTimeout, it will be deactivated.
     * 
     */
    int deactivateTimeout;

    /**
     * @brief Constructor for the WebServer class
     * 
     * The WebServer constructor initializes the freeAtTime variable to a value that will deactivate the server immediately. The deactivateTimeout variable is set to the specified value.
     * 
     * @param deactivateTimeout The time to deactivate the server after processing a request
     */
    WebServer(int deactivateTimeout);

    /**
     * @brief Process a request and update the free time
     * 
     * The ProcessRequest function takes a Request object and updates the freeAtTime variable to the current time plus the processing time of the request.
     * 
     * @param request The Request object to process
     * @param currentTime The current simulation time
     */
    void ProcessRequest(Request request, int currentTime);

    /**
     * @brief Check if the server is free at the current time
     * 
     * The IsFree function checks if the server is free at the current simulation time. If the current time is greater than or equal to freeAtTime, the server is considered free.
     * 
     * @param currentTime The current simulation time
     * @return true if the server is free, false otherwise
     */
    bool IsFree(int currentTime);

    /**
     * @brief Check if the server is activated
     * 
     * The IsActivated function checks if the server is activated at the current simulation time. If the current time is less than freeAtTime plus deactivateTimeout, the server is considered activated.
     * 
     * @param currentTime The current simulation time
     * @return true if the server is activated, false otherwise
     */
    bool IsActivated(int currentTime);

    /**
     * @brief Print the status of the server
     * 
     * The Print function displays the current status of the server, including the time it will be free, and whether it is active or deactivated.
     * 
     * @param currentTime The current simulation time
     */
    void Print(int currentTime);
};

