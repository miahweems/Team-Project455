#include <iostream>
#include <string>
#include "Customer.h"
#include "CustomerManager.cpp"
#include "Product.h"
#include "ProductManager.cpp"
#include "Transaction.h"
#include "TransactionManager.cpp"

/*
    Return Type: Void
    No Params
    Use: Displays Main Menu of Command
    Line Interface
*/
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
/*
    Return Type: Void
    No Params
    Use: Displays Main Menu of Manager
    Interface
*/
void managerMenu() {
    std::cout << "===== Manager Page =====" << std::endl;
    std::cout << "===== Select Your Task =====" << std::endl;
    std::cout << "===== By Entering The Corresponding Digit =====" << std::endl;

    std::cout << "===== 1. Customer Removal =====" << std::endl;
    std::cout << "===== 2. Product Addition =====" << std::endl;
    std::cout << "===== 3. Product Removal =====" << std::endl;
    std::cout << "===== 4. View Customer By ID =====" << std::endl;
    std::cout << "===== 5. Assign Reward Points =====" << std::endl;
    std::cout << "===== 6. Exit =====" << std::endl;

    std::cout << "Enter your choice (1-6): ";
}

/*
    Return Type: bool
    Param: int to represent user's choice in manager menu
    Use: Executes user's command
         
    Return's 0 when commanded to break out of the loop, otherwise returns 1
*/
bool managerTools(int managersChoice) {
    CustomerManager existingCustomer;
    ProductManager newProduct;
    ProductManager existingProduct;
    float rewardPtPercentage;
    if (managersChoice == 1) {   //Customer Removal
                int userIDtoRemove = 0;
                existingCustomer.outputUsernamesAndIDs();
                std::cout << "Enter the ID of the customer to be removed: ";
                std::cin >> userIDtoRemove;
                existingCustomer.removeCustomer(userIDtoRemove);
                std::cout << "Customer Removed Successfully!" << std::endl;
    }
    else if (managersChoice == 2) { //Product Addition
        newProduct.addProduct();
    }
    else if (managersChoice == 3) { //Product Removal
        int prodIDtoRemove = 0;
        std::cout << "Enter the ID of the product to be removed: ";
        std::cin >> prodIDtoRemove;
        existingProduct.removeProduct(prodIDtoRemove);
        std::cout << "Product Removed Successfully!" << std::endl;
    }
        else if (managersChoice == 4) { //View Customer By ID
        int userIDToFind = 0;
        std::cout << "Enter the ID of the customer to be viewed: ";
        std::cin >> userIDToFind;
        existingCustomer.outputUserInfo(userIDToFind);

    }
    else if (managersChoice == 5) {
        //implement reward points calculator
    }
    else if (managersChoice == 6) { // Exit
        std::cout << "Exiting the Program. Goodbye!" << std::endl;
        return 0;
    }
    else {
        std::cout << "Invalid choice, please try again." << std::endl;
    }
    return 1;
}

/*
    Return Type: Void
    No Params
    Use: Displays Main Menu of User's
    Interface
*/
void userMenu() 
{
    std::cout << "===== User Page =====" << std::endl;
    std::cout << "===== Select Your Task =====" << std::endl;
    std::cout << "===== By Entering The Corresponding Digit =====" << std::endl;

    std::cout << "===== 1. Shopping =====" << std::endl;
    std::cout << "===== 2. Redeem Rewards =====" << std::endl;
    std::cout << "===== 3. Exit =====" <<  std::endl;

     std::cout << "Enter your choice (1-3): ";
}

/*
    Return Type: bool
    Param: int to represent user's choice in user's menu
    Use: Executes user's command
         
    Return's 0 when commanded to break out of the loop, otherwise returns 1
*/
bool userTools(int userChoice)
{
    if (userChoice == 1){
        //Implement way for user to "shop"
    }
    else if (userChoice == 2){
        //Implement way for user to Redeem Rewards
    }
    else if (userChoice == 3){
        std::cout << "Exiting the Program. Goodbye!" << std::endl;
        return 0;
    }
    else {
        std::cout << "Invalid choice, please try again." << std::endl;
    }
    return 1;
}


int main()
{
    CustomerManager customerManager = CustomerManager();
    ProductManager productManager = ProductManager();
    TransactionManager transactionManager = TransactionManager();
    Customer user;
    int choice = 0; //users choice for CLI
    int managersChoice = 0; //managers choice for CLI
    int userChoice = 0; //choice for user menu
    std::string usernameEntered; //string var to hold the username entered by the user
    while(true)
    {
        mainMenu();
        std::cin >> choice;

        if (choice == 1) {
            int managersChoice = 0; //managers choice for CLI
            managerMenu();
            std::cin >> managersChoice;
            managerTools(managersChoice);
        }
        
        else if (choice == 2) {
            std::cout << "Enter Your Username: ";
            std::cin >> usernameEntered;
            try {
                user = customerManager.loginWithUsername(usernameEntered);
                std::cout << "Logged in as " << usernameEntered << std::endl;
                userMenu();
                std::cin >> userChoice;
            } catch (const std::invalid_argument& e) {
                std::cout << e.what() << std::endl;
            }
        }
        
        else if (choice == 3) {
            customerManager.registerCustomer();
        }
        
        else if (choice == 4) {
            std::cout << "Exiting the Program. Goodbye!" << std::endl;
            break;
        }
        
        else {
            std::cout << "Invalid choice, please try again." << std::endl;
        }

    }
    return 0;
}