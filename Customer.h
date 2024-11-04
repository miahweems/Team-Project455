#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

struct Customer {
    std::string userName;
    std::string firstName;
    std::string lastName;
    int age;
    int creditCard;
    int id;
    int rewardPoints = 0;
};

#endif