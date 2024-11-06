#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include "Customer.h"
#include "bools.cpp"

class CustomerManager {
private:
    std::ofstream outfile;
    std::ifstream readfile;
    std::vector<Customer> customerVector;
    const std::string TAB = "    ";
    const std::string CUSTID = "CustID";
    const std::string FILE_NAME = "registered.txt";
public:
    CustomerManager(/* args */);

    ~CustomerManager();

    void registerCustomer();

    void saveCustomers();

    void removeCustomer(int id);

    void readCustomers();

    bool usernameUnique(const std::string &username);

    bool creditcardUnique(const std::string &creditcard);

    int uniqueID();

    Customer loginWithUsername(std::string username);

    void outputUsernamesAndIDs();
};

//Class init
CustomerManager::CustomerManager(/* args */) {
}

//Destructor
CustomerManager::~CustomerManager() {
    outfile.close();
}

/*
 * registerCustomer Function
 *
 * This takes all inputs from user registering an account and generates a ten-digit ID for them,
 * then appends them to the customer vector of type Customer (Customer.h).
 *
 * Then is saves the new customer to txt file with saveCustomers() Function.
 */
void CustomerManager::registerCustomer() {
    while (true) {
        Customer newCustomer;
        Customer existingCustomer;

        std::cout << "Enter your Username: ";
        std::cin >> newCustomer.userName;
        if (usernameUnique(newCustomer.userName) && !isValidUsername(newCustomer.userName)) {
            std::cerr << "\nInvalid Username! Must start with U, less than ten characters, followed by at most three numbers, and unique.";
            break;
        }
        std::cout << "Enter your First Name: ";
        std::cin >> newCustomer.firstName;
        if (!isValidName(newCustomer.firstName)) {
            std::cerr
                    << "\nInvalid Name! Must be less than twelve characters and not contain numbers or special characters.";
            break;
        }
        std::cout << "Enter your Last Name: ";
        std::cin >> newCustomer.lastName;
        if (!isValidName(newCustomer.firstName)) {
            std::cerr
                    << "\nInvalid Name! Must be less than twelve characters and not contain numbers or special characters.";
            break;
        }
        std::cout << "Enter your Age: ";
        std::cin >> newCustomer.age;
        if (!isValidAge(newCustomer.age)) {
            std::cerr << "\nInvalid Age! Must be in between 18 and 100 and not start with zero.";
            break;
        }
        std::cout << "Enter your Credit Card Information: ";
        std::cin >> newCustomer.creditCard;
        if (creditcardUnique(newCustomer.creditCard) && !isValidCreditCard(newCustomer.creditCard)) {
            std::cerr << "\nInvalid Credit Card! Must be in xxxx-xxxx-xxxx format, cannot start with zero, \ndigits between zero and nine, and uniqe.";
            break;
        }

        newCustomer.id = uniqueID();

        customerVector.push_back(newCustomer);
        saveCustomers();
        break;
    }
}

/*
 * usernameUnique Function
 *
 * This function looks at each username in the vector and compares it to the username parameter, then returns true if
 * the username matches, then false if there is no match.
 */

bool CustomerManager::usernameUnique(const std::string &username) {
    for (const auto &customer: customerVector) {
        if (customer.userName == username) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}

/*
 * creditcardUnique Function
 *
 * This function looks through each card in the vector and compares it to the credit card parameter, there returns true
 * if the card matches, then false if there is no match.
 */
bool CustomerManager::creditcardUnique(const std::string &creditcard) {
    for (const auto &customer: customerVector) {
        if (customer.creditCard == creditcard) {
            return true;
        } else {
            continue;
        }
    }
    return false;
}

/*
 * uniqueID function
 *
 * this function creates a random number of ten digits and checks if there are no other ids to compare to. If there is
 * it loops through each id and sees if the id matches and returns the id. Else it creates and new one and restarts
 * the process.
 */
int CustomerManager::uniqueID() {
    srand(time(0));
    int id = rand() % (int(pow(10, 10)) - int(pow(10, 9))) + int(pow(10, 9));
    while (true) {
        if (customerVector.size() == 0) {
            return id;
        } else
            for (const auto &customer: customerVector) {
                if (customer.id != id) {
                    return id;
                } else {
                    continue;
                }
            }
        srand(time(0));
        id = rand() % (int(pow(10, 10)) - int(pow(10, 9))) + int(pow(10, 9));
    }
}


/*
 * saveCustomers Function
 *
 * This function opens the txt file and writes every customers information from the customerVector
 * of type Customer (Customer.h), this needs to be called with after each addition or deletion of
 * a customer to retain the txt validity.
 */
void CustomerManager::saveCustomers() {
    outfile.open(FILE_NAME);
    int count = 1;
    for (const Customer customer: customerVector) {
        if (outfile.is_open()) {
            outfile << "customer " << count << std::endl;
            outfile << TAB + "CustID" << customer.id << std::endl;
            outfile << TAB << customer.userName << std::endl;
            outfile << TAB << customer.firstName << std::endl;
            outfile << TAB << customer.lastName << std::endl;
            outfile << TAB << customer.age << std::endl;
            outfile << TAB << customer.creditCard << std::endl;
            outfile << TAB << customer.rewardPoints << std::endl;

            ++count;
        }
    }
    outfile.close();
}

/*
 *  readCustomers Function
 *
 *  This reads the text file and stores each entry into a vector of type Customer (from Customer.h) to be manipulated
 */
void CustomerManager::readCustomers() {
    readfile.open(FILE_NAME);
    std::vector<Customer> tempCustomers;
    std::string line;
    while (getline(readfile, line)) {

        if (line.find("customer") != std::string::npos) {
            Customer customer;
            getline(readfile, line);
            customer.id = std::stoi(line.substr(TAB.length() + CUSTID.length()));
            getline(readfile, line);
            customer.userName = line.substr(TAB.length());
            getline(readfile, line);
            customer.firstName = line.substr(TAB.length());
            getline(readfile, line);
            customer.lastName = line.substr(TAB.length());
            getline(readfile, line);
            customer.age = line.substr(TAB.length());
            getline(readfile, line);
            customer.creditCard = line.substr(TAB.length());
            getline(readfile, line);
            customer.rewardPoints = std::stoi(line.substr(TAB.length()));
            tempCustomers.push_back(customer);
        }
    }
    customerVector = tempCustomers;

    readfile.close();
}

/*
 * loginWithUsername Function
 *
 * This function looks through each username in the customer vector and finds the matching username and returns the
 * customer struct with all the user's information. If username is not found then it cerrs that the account doesn't
 * exist.
 */
Customer CustomerManager::loginWithUsername(std::string username) {
    for (const auto &account: customerVector) {
        if (account.userName == username) {
            return account;
        } else {
            continue;
        }
    }
    std::cerr << "Account doesn't exits.";
}

/*
 * outputCustomersAndID Function
 *
 * This function displays each account's username and ID
 *
 * Used for the manager to see what user to delete
 */

void CustomerManager::outputUsernamesAndIDs() {
    for (const auto &account: customerVector) {
        std::cout << "Username: " << account.userName << " ID: " << account.id;
    }
}


/*
 * removeCustomer Function
 *
 * This function looks through each id in the customerVector and erases the customer with the
 * giving id in the parameter.
 *
 */
void CustomerManager::removeCustomer(int id) {
    for (int i = 0; i < customerVector.size(); ++i) {
        if (id == customerVector[i].id) {
            customerVector.erase(customerVector.begin() + i);
        } else {
            continue;
        }
    }
    saveCustomers();
}