#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "Transaction.h"
#include "Product.h"

class TransactionManager {
private:
    std::ofstream outfile;
    std::ifstream infile;
    std::vector<Transaction> transactionVector;
    std::vector<int> customerIDs;
    const std::string FILE_NAME = "transactions.txt";
    const std::string TAB = "    ";
    const std::string TRANSID = "Transaction ID: ";
    const std::string USERID = "Users ID: ";
    const std::string PRODUCTS = "Product IDs: ";
    const std::string TOTALAMNT = "Total Amount: $";
    const std::string TOTALRWDPTS = "Reward Points: ";


public:
    TransactionManager();

    ~TransactionManager();

    void addTransaction(const int userID, const std::vector<int> &productIDs, float totalAmount, int rewardPoints);

    void saveTransactions();

    void loadTransactions();

    void outputTransactions();

    int uniqueID();
};

// Constructor
TransactionManager::TransactionManager() {
    loadTransactions();
}

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
void TransactionManager::addTransaction(const int userID, const std::vector<int> &productIDs, float totalAmount,
                                        int rewardPoints) {
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
    int transactionCount = 1;
    for (const Transaction &transaction: transactionVector) {
        int productCount = 1;
        if (outfile.is_open()) {
            outfile << "Transaction " << transactionCount << std::endl;
            outfile << TAB << TRANSID << transaction.transactionID << std::endl;
            outfile << TAB << USERID << transaction.userID << std::endl;

            outfile << TAB << PRODUCTS;
            for (const int &id: transaction.productIDs) {
                outfile << "Product" << "(" << productCount << ")" << " " << id << " ";
                ++productCount;
            }
            outfile << std::endl;

            outfile << TAB << TOTALAMNT << transaction.totalAmount << std::endl;
            outfile << TAB << TOTALRWDPTS << transaction.rewardPoints << std::endl;
            ++transactionCount;
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
            transaction.transactionID = stoi(line.substr(TAB.length() + TRANSID.length()));
            getline(infile, line);
            transaction.userID = stoi(line.substr(TAB.length() + USERID.length()));
            getline(infile, line);
            std::string productsLine = line.substr(TAB.length() + PRODUCTS.length());  // Skip "Products: "
            std::istringstream productStream(productsLine);//Parse by spaces and length of each iteration
            std::string productID;
            std::vector<int> ids;
            while (productStream >> productID) {
                int i = 0;
                if (isdigit(productID[i])) {
                    ids.push_back(stoi(productID));
                } else {
                    continue;
                }
            }
            transaction.productIDs = ids;
            getline(infile, line);
            transaction.totalAmount = std::stof(
                    line.substr(TAB.length() + TOTALAMNT.length()));  // Skip "Total Amount: "
            getline(infile, line);
            transaction.rewardPoints = std::stoi(
                    line.substr(TAB.length() + TOTALRWDPTS.length())); // Skip "Reward Points: "

            tempTransactions.push_back(transaction);
        }
    }

    transactionVector = tempTransactions;
    infile.close();
}

/*
 * outputTransactions
 *
 * This function adds the ability to output each transaction when the manager might request it.
 */
void TransactionManager::outputTransactions() {
    int transactionCount = 1;
    for (const Transaction &transaction: transactionVector) {
        int productCount = 1;
        std::cout << "Transaction " << transactionCount << std::endl;
        std::cout << TAB << TRANSID << transaction.transactionID << std::endl;
        std::cout << TAB << USERID << transaction.userID << std::endl;
        std::cout << TAB << PRODUCTS;
        for (const int &productID: transaction.productIDs) {
            std::cout << "Product" << "(" << productCount << ")" << " " << productID << " ";
            productCount++;
        }
        std::cout << std::endl;
        std::cout << TAB << TOTALAMNT << transaction.totalAmount << std::endl;
        std::cout << TAB << TOTALRWDPTS << transaction.rewardPoints << std::endl;
        ++transactionCount;
    }
}

