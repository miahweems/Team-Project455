#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>
#include "Product.h"

struct Transaction {
    int transactionID;         // Unique ID for each transaction
    int userID;                // ID of the user making the transaction
    std::vector<int> productIDs; // List of product IDs purchased
    float totalAmount;          // Total amount of the transaction
    int rewardPoints = 0;                 // Reward points earned from the transaction
};

#endif
