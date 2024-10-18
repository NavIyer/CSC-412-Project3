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

/**
 * @brief Load balancer class for managing web servers and requests
 * 
 * The LoadBalancer class is responsible for managing a set of WebServer objects and a queue of Request objects. It will process requests in the queue and assign them to the servers as they become available. The LoadBalancer class will also keep track of statistics such as the number of requests processed, dropped, and completed.
 * 
 */
class LoadBalancer {
public:
    /**
     * @brief List of WebServer objects managed by the LoadBalancer
     * 
     * The servers vector contains all of the WebServer objects that the LoadBalancer is managing. Each WebServer object represents a single server in the load balancer system.
     * 
     */
    vector<WebServer> servers;

    /**
     * @brief Queue of incoming Request objects
     * 
     * The requestQueue is a queue of Request objects that are waiting to be processed by the load balancer. Requests are added to the queue when they arrive and are removed when they are assigned to a server.
     * 
     */
    queue<Request> requestQueue;

    /**
     * @brief Current simulation time
     * 
     * The currentTime variable represents the current time in the simulation. It is incremented by one each time the Tick function is called.
     * 
     */
    int currentTime;

    /**
     * @brief Number of requests processed
     * 
     * The requestsProcessed variable keeps track of the total number of requests that have been processed by the load balancer.
     * 
     */
    int requestsProcessed;

    /**
     * @brief Number of requests dropped
     * 
     * The requestsDropped variable keeps track of the total number of requests that have been dropped by the load balancer due to a full queue.
     * 
     */
    int requestsDropped;

    /**
     * @brief Number of requests completed
     * 
     * The requestsCompleted variable keeps track of the total number of requests that have been completed by the load balancer.
     * 
     */
    int requestsCompleted;

    /**
     * @brief Maximum queue size
     * 
     * The maxQueueSize variable represents the maximum number of requests that the queue can hold. If the queue is full and a new request arrives, it will be dropped.
     * 
     */
    int maxQueueSize;

    /**
     * @brief Constructor for the LoadBalancer class
     * 
     * The LoadBalancer constructor initializes the servers vector with the specified number of WebServer objects, each with the given deactivateTimeout value. It also initializes the currentTime, requestsProcessed, requestsDropped, and requestsCompleted variables to zero, and sets the maxQueueSize to the specified value.
     * 
     * @param numServers The number of WebServer objects to create
     * @param deactivateTimeout The time to deactivate a server after processing a request
     * @param maxQueueSize The maximum size of the request queue
     */
    LoadBalancer(int numServers, int deactivateTimeout, int maxQueueSize);

    /**
     * @brief Enqueue a vector of Request objects
     * 
     * The EnqueueRequests function adds a vector of Request objects to the request queue. If the queue is full, requests will be dropped and the requestsDropped counter will be incremented.
     * 
     * @param requests A vector of Request objects to add to the queue
     */
    void EnqueueRequests(vector<Request> requests);

    /**
     * @brief Process a single time step in the simulation
     * 
     * The Tick function advances the simulation by one time step. It checks for free servers, assigns requests to servers, and updates the server status. It also increments the currentTime variable.
     * 
     */
    void Tick();

    /**
     * @brief Get the number of active servers
     * 
     * The NumActiveServers function returns the number of servers that are awake and ready to process requests.
     * 
     * @return The number of active servers
     */
    int NumActiveServers();

    /**
     * @brief Get the number of free servers
     * 
     * The NumFreeServers function returns the number of servers that are free and not currently processing a request.
     * 
     * @return The number of free servers
     */
    int NumFreeServers();

    /**
     * @brief Print the current status of the load balancer
     * 
     * The Print function displays the current status of the load balancer, including the number of active and currently-processing servers, the number of requests processed, dropped, and completed, and the size of the request queue.
     * 
     */
    void Print();
};
