#include <iostream>
#include <string>
#include "Customer.h"
#include "CustomerManager.cpp"
#include "Product.h"
#include "ProductManager.cpp"
#include "Transaction.h"
#include "TransactionManager.cpp"
#include "bools.cpp"

void mainMenu() {
    std::cout << "===== Welcome =====" << std::endl;
    std::cout << "===== Select Your Role =====" << std::endl;
    std::cout << "===== By Entering The Corresponding Digit =====" << std::endl;

    std::cout << "===== 1. Manager =====" << std::endl;
    std::cout << "===== 2. Returning Customer =====" << std::endl;
    std::cout << "===== 3. New Customer =====" << std::endl;
    std::cout << "===== 4. Exit =====" << std::endl;

    std::cout << "=======================" << std::endl;
    std::cout << "Enter your choice (1-4): ";

}

void managerMenu() {
    std::cout << "===== Manager Page =====" << std::endl;
    std::cout << "===== Select Your Task =====" << std::endl;
    std::cout << "===== By Entering The Corresponding Digit =====" << std::endl;

    std::cout << "===== 1. Customer Removal =====" << std::endl;
    std::cout << "===== 2. Product Addition =====" << std::endl;
    std::cout << "===== 3. Product Removal =====" << std::endl;
    std::cout << "===== 4. View Customer By ID =====" << std::endl;
    std::cout << "===== 5. Exit =====" << std::endl;

    std::cout << "Enter your choice (1-5): ";
}



int main() 
{
    int choice = 0; //users choice for CLI
    int managersChoice = 0; //managers choice for CLI
    CustomerManager newCustomer;
    CustomerManager existingCustomer;
    ProductManager newProduct;
    ProductManager existingProduct;
    Customer customer;
    std::string usernameEntered;
    while(1) 
    {
        mainMenu();
        std::cin >> choice;

        if (choice == 1) {
            int managersChoice = 0; //managers choice for CLI
            managerMenu();
            std::cin >> managersChoice;

            if (managersChoice == 1) {
                int userIDtoRemove = 0;
                existingCustomer.outputUsernamesandIDs();
                std::cout << "Enter the ID of the customer to be removed: ";
                std::cin >> IDtoRemove;
                existingCustomer.removeCustomer(IDtoRemove);
                std::cout << "Customer Removed Successfully!" << std::endl;
            }
            else if (managersChoice == 2) {
                newProduct.addProduct();
            }
            else if (managersChoice == 3) {
                int prodIDtoRemove = 0;
                std::cout << "Enter the ID of the product to be removed: ";
                std::cin >> prodIDtoRemove;
                existingCustomer.removeProduct(prodIDtoRemove);
                std::cout << "Product Removed Successfully!" << std::endl;
            }
            /* else if (managersChoice == 4) {
                int userIDToFind = 0;
                std::cout << "Enter the ID of the customer to be viewed: ";
                std::cin >> userIDToFind;

            }
            */
            else if (managersChoice == 5) {
                std::cout << "Exiting the Program. Goodbye!" << std::endl;
                break;
            }
            else {
                std::cout << "Invalid choice, please try again." << std::endl;
            }
        }
        
        else if (choice == 2) {
            std::cout << "Enter Your Username: " << std::endl;
            std::cin >> usernameEntered;
            existingCustomer.loginWithUsername(usernameEntered);
            std::cout << "Logged in as " << usernameEntered << std::endl;
        }
        
        else if (choice == 3) {
            newCustomer.registerCustomer();
        }
        
        else if (choice == 4) {
            std::cout << "Exiting the Program. Goodbye!" << std::endl;
            break;
        }
        
        else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }

    }

}