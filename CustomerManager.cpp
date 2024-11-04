#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include "Customer.h"

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
    Customer newCustomer;

    std::cout << "Enter your Username: ";
    std::cin >> newCustomer.userName;
    std::cout << "Enter your First Name: ";
    std::cin >> newCustomer.firstName;
    std::cout << "Enter your Last Name: ";
    std::cin >> newCustomer.lastName;
    std::cout << "Enter your Age: ";
    std::cin >> newCustomer.age;

    //while to check all id
    srand(time(0));
    newCustomer.id = rand() % (int(pow(10, 9)) - int((pow(10, 10) - 1))) + int(pow(10, 9));

    customerVector.push_back(newCustomer);
    saveCustomers();
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
            outfile << TAB << customer.rewardPoints << std::endl;

            ++count;
        }
    }
    outfile.close();
}

/*
 * removeCustomer Function
 *
 * This function looks through each id in the customerVector and erases the customer with the
 * giving id in the parameter.
 */
void CustomerManager::removeCustomer(int id) {
    for (int i = 0; i < customerVector.size(); ++i) {
        if (id == customerVector[i].id) {
            customerVector.erase(customerVector.begin() + i);
        }
    }
    saveCustomers();
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
            customer.age = std::stoi(line.substr(TAB.length()));
            getline(readfile, line);
            customer.rewardPoints = std::stoi(line.substr(TAB.length()));
            tempCustomers.push_back(customer);
        }
    }
    customerVector = tempCustomers;

    readfile.close();
}