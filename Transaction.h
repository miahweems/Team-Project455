#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <vector>

struct Transaction {
    int transactionID;         // Unique ID for each transaction
    std::string userID;                // ID of the user making the transaction
    std::vector<std::string> productIDs; // List of product IDs purchased
    float totalAmount = 0.0f;          // Total amount of the transaction
    int rewardPoints = 0;              // Reward points earned from the transaction
};

#endif
