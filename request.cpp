/**
 * @file request.cpp
 * @brief Implementation of the Request class
 */

#include "request.h"


Request::Request(int maxProcessingTime)
{
    ipIn = RandomIp();
    ipOut = RandomIp();
    processingTime = rand() % maxProcessingTime + 1;
    jobType = (rand() % 2 == 0) ? 'P' : 'S';
}

void Request::Print()
{
    cout << "Incoming IP: " << ipIn << ", Outgoing IP: " << ipOut << ", Processing Time: " << processingTime << ", Job Type: " << jobType << endl;
}
