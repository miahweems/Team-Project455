#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Product.h"

class ProductManager {
private:
    std::ofstream outfile;
    std::ifstream infile;
    std::vector<Product> productVector;
    const std::string TAB = "    ";
    const std::string PRODID_PREFIX = "Prod";
    const std::string FILE_NAME = "products.txt";

public:
    ProductManager();
    ~ProductManager();

    void addProduct();
    void saveProducts();
    void removeProduct(int productID);
    void loadProducts();
};

// Constructor
ProductManager::ProductManager() {}

// Destructor
ProductManager::~ProductManager() {
    outfile.close();
}

/*
 * addProduct Function
 *
 * This function prompts the user to input all details for adding a new product. 
 * It generates a unique ID for the product, then appends it to the product vector.
 * Finally, it saves the new product to the products file with saveProducts().
 */
void ProductManager::addProduct() {
    Product newProduct;
    
    std::cout << "Enter Product Name: ";
    std::cin.ignore();
    std::getline(std::cin, newProduct.productName);
    std::cout << "Enter Product Price: ";
    std::cin >> newProduct.productPrice;
    std::cout << "Enter Product Stock: ";
    std::cin >> newProduct.productStock;

    // Generate unique product ID
    static int productIDCounter = 10000;  // For example, starting ID sequence
    newProduct.productID = PRODID_PREFIX + std::to_string(productIDCounter++);
    
    productVector.push_back(newProduct);
    saveProducts();
}

/*
 * saveProducts Function
 *
 * This function opens the products file and writes each product's information from the 
 * product vector. It should be called after every addition or deletion to keep the file updated.
 */
void ProductManager::saveProducts() {
    outfile.open(FILE_NAME);
    int count = 1;
    for (const Product& product : productVector) {
        if (outfile.is_open()) {
            outfile << "product " << count++ << std::endl;
            outfile << TAB << product.productID << std::endl;
            outfile << TAB << product.productName << std::endl;
            outfile << TAB << product.productPrice << std::endl;
            outfile << TAB << product.productStock << std::endl;
        }
    }
    outfile.close();
}

/*
 * removeProduct Function
 *
 * This function searches the product vector for a product with the specified ID and removes it.
 * It then calls saveProducts() to update the products file.
 */
void ProductManager::removeProduct(int productID) {
    for (int i = 0; i < productVector.size(); ++i) {
        if (productVector[i].productID == productID) {
            productVector.erase(productVector.begin() + i);
            break;
        }
    }
    saveProducts();
}

/*
 * loadProducts Function
 *
 * This function reads products from the products file and loads each product entry into the product vector.
 */
void ProductManager::loadProducts() {
    infile.open(FILE_NAME);
    std::vector<Product> tempProducts;
    std::string line;

    while (getline(infile, line)) {
        if (line.find("product") != std::string::npos) {
            Product product;
            getline(infile, line);
            product.productID = line.substr(TAB.length());
            getline(infile, line);
            product.productName = line.substr(TAB.length());
            getline(infile, line);
            product.productPrice = std::stof(line.substr(TAB.length()));
            getline(infile, line);
            product.productStock = std::stoi(line.substr(TAB.length()));
            tempProducts.push_back(product);
        }
    }

    productVector = tempProducts;
    infile.close();
}

#endif
