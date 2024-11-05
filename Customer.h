#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <string>

struct Customer {
    std::string userName;
    std::string firstName;
    std::string lastName;
    std::string age;
    std::string creditCard;
    int id;
    int rewardPoints = 0;
};

#endif