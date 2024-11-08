#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "Transaction.h"
#include "ProductManager"
#include "Product.h"

class TransactionManager {
private:
    std::ofstream outfile;
    std::ifstream infile;
    std::vector<Transaction> transactionVector;
    const std::string FILE_NAME = "transactions.txt";
    const std::string TAB = "    ";

public:
    TransactionManager();
    ~TransactionManager();

    void addTransaction(const int userID, const std::vector<int>& productIDs, float totalAmount, int rewardPoints);
    void saveTransactions();
    void loadTransactions();
    int uniqueID();
};

// Constructor
TransactionManager::TransactionManager() {}

// Destructor
TransactionManager::~TransactionManager() {
    outfile.close();
}

/*
 * addTransaction Function
 *
 * Adds a new transaction with details provided and assigns a unique transaction ID.
 * Appends it to the transaction vector and then calls saveTransactions() to save it to a file.
 */
void TransactionManager::addTransaction(const int userID, const std::vector<int>& productIDs, float totalAmount, int rewardPoints) {
    Transaction newTransaction;

    newTransaction.transactionID = uniqueID();
    newTransaction.userID = userID;
    newTransaction.productIDs = productIDs;
    newTransaction.totalAmount = totalAmount;
    newTransaction.rewardPoints = rewardPoints;

    transactionVector.push_back(newTransaction);
    saveTransactions();
}

int TransactionManager::uniqueID() {
    srand(time(nullptr));
    int id = rand() % (int(pow(10, 5)) - int(pow(10, 4))) + int(pow(10, 4)); // 5-digit ID range
    while (true) {
        if (transactionVector.empty()) {
            return id;
        } else
            for (const Transaction &transaction: transactionVector) {
                if (transaction.transactionID != id) {
                    return id;
                } else {
                    continue;
                }
            }
        srand(time(nullptr));
        id = rand() % (int(pow(10, 5)) - int(pow(10, 4))) + int(pow(10, 4));
    }
}

/*
 * saveTransactions Function
 *
 * Writes all transactions from the transaction vector to transactions.txt.
 */
void TransactionManager::saveTransactions() {
    outfile.open(FILE_NAME);
    int count = 1;
    int productCount = 1;
    for (const Transaction& transaction : transactionVector) {
        if (outfile.is_open()) {
            outfile << "Transaction " << count++ << std::endl;
            outfile << TAB <<transaction.transactionID << std::endl;
            outfile << TAB << transaction.userID << std::endl;

            outfile << TAB << "Products: ";
            for (const int &id : transaction.productIDs) {
                outfile << "Product " << productCount << " " << id << " ";
            }
            outfile << std::endl;

            outfile << TAB << "Total Amount: " << transaction.totalAmount << std::endl;
            outfile << TAB << "Reward Points: " << transaction.rewardPoints << std::endl;

            ++count;
            ++productCount
        }
    }
    outfile.close();
}

/*
 * loadTransactions Function
 *
 * Reads from transactions.txt and loads each transaction into the transaction vector.
 */
void TransactionManager::loadTransactions() {
    infile.open(FILE_NAME);
    std::vector<Transaction> tempTransactions;
    std::string line;

    while (getline(infile, line)) {
        if (line.find("Transaction") != std::string::npos) {
            Transaction transaction;
            getline(infile, line);
            transaction.transactionID = stoi(line.substr(TAB.length()));
            getline(infile, line);
            transaction.userID = stoi(line.substr(TAB.length()));

            getline(infile, line);
            std::string productsLine = line.substr(TAB.length() + 10);  // Skip "Products: "
            std::istringstream productStream(productsLine);//Parse by spaces and length of each iteration
            std::string productID;
            while (productStream >> productID) {
                transaction.productIDs.push_back(productID);
            }

            getline(infile, line);
            transaction.totalAmount = std::stof(line.substr(TAB.length() + 14));  // Skip "Total Amount: "
            getline(infile, line);
            transaction.rewardPoints = std::stoi(line.substr(TAB.length() + 15)); // Skip "Reward Points: "

            tempTransactions.push_back(transaction);
        }
    }

    transactionVector = tempTransactions;
    infile.close();
}

