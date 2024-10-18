/**
 * @file main.cpp
 * @author Naveen Iyer
 * @brief Main driver file for the load balancer simulation
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 * @mainpage Load Balancer Simulation
 * 
 * This is a simple load balancer simulation that models a set of web servers processing incoming requests. The load balancer assigns requests to servers based on availability and deactivates servers after a specified timeout. Requests are enqueued in a queue and dropped if the queue is full.
 * 
 * The simulation runs for a specified number of cycles, and new requests are generated randomly at each cycle. The simulation tracks the number of requests processed, dropped, and completed, as well as the number of active and free servers at any given time.
 * 
 * The simulation is implemented using three main classes:
 * 
 * - Request: Represents an incoming request with an incoming IP address, outgoing IP address, processing time, and job type.
 * 
 * - WebServer: Represents a web server that can process requests. It tracks when the server will be free to process a new request and when it should be deactivated after processing a request.
 * 
 * - LoadBalancer: Manages a set of web servers and a queue of incoming requests. It assigns requests to servers as they become available and keeps track of statistics such as the number of requests processed, dropped, and completed.
 * 
 * The simulation is driven by the main function in main.cpp, which initializes the load balancer, generates initial requests, and runs the simulation for a specified number of cycles. The main function prints the status of the load balancer at regular intervals and displays the final statistics at the end of the simulation.
 * 
 * To run the simulation, compile the code using the provided Makefile and run the executable with two arguments: the number of web servers and the time to run the simulation in cycles. For example:
 * 
 * ./loadbalancer 5 1000
 * 
 * This will run the simulation with 5 web servers for 1000 cycles.
 * 
 */

#include <iostream>
#include "loadbalancer.h"
#include "request.h"

using std::cout;
using std::endl;
using std::string;

/**
 * @brief Main driver function for the load balancer simulation
 * 
 * @param argc Number of arguments
 * @param argv Arguments
 * @return int Exit code
 */
int main(int argc, char* argv[])
{
    /////// Arguments //////
    if (argc != 3)
    {
        cout << "Error: Two arguments expected." << endl;
        cout << "Usage: ./loadbalancer <number of web servers> <time to run (cycles)>" << endl;
        return 1;
    }

    int numServers = atoi(argv[1]);
    int runLength = atoi(argv[2]);
    if (numServers <= 0 || runLength <= 0)
    {
        cout << "Error: Arguments must be positive integers." << endl;
        return 1;
    }

    /////// Initialize Load Balancer //////
    int maxQueueSize = numServers * 100;
    int deactivateTimeout = 10;
    cout << "Number of web servers: " << numServers << endl;
    cout << "Time to run (cycles): " << runLength << endl;
    cout << "Timeout to deactivate servers: " << deactivateTimeout << endl;
    cout << "Max queue size: " << maxQueueSize << endl;
    cout << "Range for request processing time: 1-10 cycles" << endl;
    cout << "Initial queue size: " << maxQueueSize << endl;
    cout << "--- Begin Simulation ---" << endl;
    LoadBalancer lb(numServers, deactivateTimeout, maxQueueSize);
    lb.Print();

    /////// Generate Initial Requests //////
    srand(time(NULL));
    int maxProcessingTime = 10;

    vector<Request> initialRequests;
    for (int i = 0; i < maxQueueSize; i++)
    {
        initialRequests.push_back(Request(maxProcessingTime));
    }
    lb.EnqueueRequests(initialRequests);

    /////// Run Load Balancer //////
    int currentTime;
    const int printInterval = 10;
    for (currentTime = 0; currentTime < runLength; currentTime++)
    {
        // 5% chance of generating new requests
        if (rand() % 20 == 0)
        {
            vector<Request> newRequests;
            for (int i = 0; i < rand() % (numServers * 20); i++)  // Random number of requests between 0 and numServers*20
            {
                newRequests.push_back(Request(maxProcessingTime));
            }
            lb.EnqueueRequests(newRequests);
        }

        lb.Tick();

        if (currentTime % printInterval == 0)
        {
            lb.Print();
        }
    }

    cout << "--- End of Simulation ---" << endl;
    cout << "Servers currently-processing at end: " << numServers - lb.NumFreeServers() << endl;
    cout << "Servers free at end: " << lb.NumFreeServers() << endl;
    cout << "Servers active at end: " << lb.NumActiveServers() << endl;
    cout << "Servers deactivated at end: " << numServers - lb.NumActiveServers() << endl;
    cout << "Total requests processed by servers: " << lb.requestsProcessed << endl;
    cout << "Total requests dropped: " << lb.requestsDropped << endl;
    cout << "Total requests completed: " << lb.requestsCompleted << endl;
    cout << "Final queue size: " << lb.requestQueue.size() << endl;

}

