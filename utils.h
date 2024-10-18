/**
 * @file utils.cpp
 * @brief Utility functions for the load balancer simulation
 */

#pragma once

#include <string>
using std::string;

/**
 * @brief Generate a random IP address
 * 
 * The RandomIp function generates a random IP address in the form "xxx.xxx.xxx.xxx", where each "xxx" is a random number between 0 and 255.
 * 
 * @return A random IP address
 */
string RandomIp();

