#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Product.h"
#include "bools.cpp"

class ProductManager {
private:
    std::ofstream outfile;
    std::ifstream infile;
    std::vector<Product> productVector;
    std::vector<Product> productCart;
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
    int uniqueID();
    void addProductToCart(int id);
    void displayCart();
    float totalPriceOfCart();
};

// Constructor
ProductManager::ProductManager() {
}

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
    while (true) {
        Product newProduct;

        std::cout << "Enter Product Name: ";
        std::cin >> newProduct.productName;
        if (!isValidName(newProduct.productName)) {
            std::cerr << "\nInvalid Product Name! Must be less than 20 characters and not contain special characters.";
            continue;
        }

        std::cout << "Enter Product Price: $";
        std::cin >> newProduct.productPrice;
        /*if (!isValidProductPrice(newProduct.productPrice)) {
            std::cerr << "\nInvalid Product Price! Must be a positive number.";
            continue;
        }
*/
        std::cout << "Enter Product Stock: ";
        std::cin >> newProduct.productStock;
        if (!isPositive(newProduct.productStock)) {
            std::cerr << "\nInvalid Product Stock! Must be a positive integer.";
            continue;
        }


        newProduct.productID = uniqueID();

        productVector.push_back(newProduct);
        saveProducts();
        break;
    }
}

/*
 * uniqueID function
 *
 * this function creates a random number of 5 digits and checks if there are no other ids to compare to. If there is
 * it loops through each id and sees if the id matches and returns the id. Else it creates and new one and restarts
 * the process.
 */
int ProductManager::uniqueID() {
    srand(time(nullptr));
    int id = rand() % (int(pow(10, 5)) - int(pow(10, 4))) + int(pow(10, 4)); // 5-digit ID range
    while (true) {
        if (productVector.size() == 0) {
            return id;
        } else
            for (const Product &product: productVector) {
                if (product.productID != id) {
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

void ProductManager::addProductToCart(int id) {
    for (const Product product : productVector) {
        if (product.productID == id) {
            productCart.push_back(product);
        } else {
            continue;
        }
    }
}

void ProductManager::displayCart() {
    std::cout << "===== Cart =====" << std::endl;
    for (const Product product : productCart) {
         std::cout << product.productName << " $" << product.productPrice << std::endl;
    }

    std::cout << "================" << std::endl << "Total: " << totalPriceOfCart();
}

float ProductManager::totalPriceOfCart() {
    float total = 0;
    for (const Product product : productCart) {
        total = total + std::stof(product.productPrice);
    }
    total = std::round(total * 100.f) / 100.f;
    return total;
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
            product.productID = std::stoi(line.substr(TAB.length()));
            getline(infile, line);
            product.productName = line.substr(TAB.length());
            getline(infile, line);
            product.productPrice = line.substr(TAB.length());
            getline(infile, line);
            product.productStock = std::stoi(line.substr(TAB.length()));
            tempProducts.push_back(product);
        }
    }

    productVector = tempProducts;
    infile.close();
}

