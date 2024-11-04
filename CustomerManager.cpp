#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <algorithm>
#include "Customer.h"

class CustomerManager
{
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

CustomerManager::CustomerManager(/* args */)
{
    readCustomers();
    while(true) {
        registerCustomer();
    }
}

CustomerManager::~CustomerManager()
{
    outfile.close();
}

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
void CustomerManager::saveCustomers() {
    outfile.open(FILE_NAME);
    int count = 1;
    for (const Customer customer : customerVector) {
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
void CustomerManager::removeCustomer(int id) {
    for (int i = 0; i < customerVector.size(); ++i){
        if(id == customerVector[i].id){
            customerVector.erase(customerVector.begin() + i);
        }
    }
    saveCustomers();
}

void CustomerManager::readCustomers() {
    readfile.open(FILE_NAME);
    std::vector<Customer> tempCustomers;
    std::string line;
    while(getline(readfile, line)){

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

int main() {
    CustomerManager();
}