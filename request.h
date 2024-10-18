# pragma once

#include <iostream>
#include "utils.h"
using std::string;
using std::cout;
using std::endl;

/**
 * @brief Request class for representing incoming requests
 * 
 * The Request class represents an incoming request to the load balancer. Each request has an incoming IP address, an outgoing IP address, a processing time, and a job type (Processing or Streaming, represented by 'P' or 'S').
 * 
 */
class Request {
public:
    /**
     * @brief Incoming IP address
     * 
     * The ipIn variable represents the incoming IP address of the request.
     * 
     */
    string ipIn;

    /**
     * @brief Outgoing IP address
     * 
     * The ipOut variable represents the outgoing IP address of the request.
     * 
     */
    string ipOut;

    /**
     * @brief Processing time
     * 
     * The processingTime variable represents the time it takes for the request to be processed by the server.
     * 
     */
    int processingTime;

    /**
     * @brief Job type
     * 
     * The jobType variable represents the type of job the request is (Processing or Streaming, represented by 'P' or 'S').
     * 
     */
    char jobType;

    /**
     * @brief Constructor for the Request class
     * 
     * The Request constructor generates a random incoming and outgoing IP address, a random processing time, and a random job type for the request.
     * 
     * @param maxProcessingTime The maximum processing time for the randomly-generated request
     */
    Request(int maxProcessingTime);

    /**
     * @brief Print the details of the request
     * 
     * The Print function displays the details of the request, including the incoming and outgoing IP addresses, the processing time, and the job type.
     * 
     */
    void Print();
};

