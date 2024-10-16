#include "request.h"

#include "utils.h"

using std::cout;
using std::endl;

Request::Request(int runLength)
{
    ipIn = RandomIp();
    ipOut = RandomIp();
    arrivalTime = rand() % runLength;
    jobType = (rand() % 2 == 0) ? 'P' : 'S';
}

void Request::Print()
{
    cout << "Incoming IP: " << ipIn << ", Outgoing IP: " << ipOut << ", Arrival Time: " << arrivalTime << ", Job Type: " << jobType << endl;
}
