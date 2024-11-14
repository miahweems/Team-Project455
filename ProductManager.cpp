#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Product.h"
#include "Customer.h"
#include "bools.h"

class ProductManager {
private:
    std::ofstream outfile;
    std::ifstream infile;
    std::vector<Product> productVector;
    std::vector<Product> productCart;
    float rewardPercent = .1;
    const std::string TAB = "    ";
    const std::string PRODID_PREFIX = "Prod";
    const std::string FILE_NAME = "products.txt";
    const std::string PRODID = "Product ID: ";
    const std::string PRODNAME = "Product Name: ";
    const std::string PRODPRICE = "Product Price: $";
    const std::string PRODSTOCK = "Product Stock: ";

public:
    ProductManager();

    ~ProductManager();

    void addProduct();

    void saveProducts();

    void removeProduct(int productID);

    void loadProducts();

    void outputProducts();

    int uniqueID();

    void displayAvalibleProducts();

    void addProductToCart(std::string availableProducts);

    void addProductToCart(int id);

    std::vector<int> gatherCartIDs();

    void displayCart();

    void removeFromCart(std::string removedProduct);

    float totalPriceOfCart();

    float setRewardPercent(float percent);

    int rewardPointsPurchase(int customerRewardPts);

    int recivePoints();

    void purchase();
};

// Constructor
ProductManager::ProductManager() {
    loadProducts();
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
            std::cout << "Invalid Product Name! Must be less than 20 characters and not contain special characters." << std::endl;
            break;
        }

        std::cout << "Enter Product Price: $";
        std::cin >> newProduct.productPrice;
        if (!isValidProductPrice(newProduct.productPrice)) {
            std::cout << "Invalid Product Price! Must be a positive number." << std::endl;
            break;
        }

        std::cout << "Enter Product Stock: ";
        std::cin >> newProduct.productStock;
        if (!isPositive(newProduct.productStock)) {
            std::cout << "Invalid Product Stock! Must be a positive integer." << std::endl;
            break;
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
    for (const Product &product: productVector) {
        if (outfile.is_open()) {
            outfile << "product " << count++ << std::endl;
            outfile << TAB << PRODID << product.productID << std::endl;
            outfile << TAB << PRODNAME << product.productName << std::endl;
            outfile << TAB << PRODPRICE << product.productPrice << std::endl;
            outfile << TAB << PRODSTOCK << product.productStock << std::endl;
        }
    }
    outfile.close();
}

void ProductManager::outputProducts() {
    int productCount = 1;
    for (const Product &product: productVector) {
        std::cout << "product " << productCount << std::endl;
        std::cout << TAB << PRODID << product.productID << std::endl;
        std::cout << TAB << PRODNAME << product.productName << std::endl;
        std::cout << TAB << PRODPRICE << product.productPrice << std::endl;
        std::cout << TAB << PRODSTOCK << product.productStock << std::endl;
        ++productCount;
    }
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
 * displayAvaliableProducts Function
 *
 * This fucnction displays all available products by setting itself to the productVector and erasing all the products that
 * have no stock left in inventory. Then displays them by product, price, and quantity left.
 */
void ProductManager::displayAvalibleProducts() {
    std::vector<Product> availableProducts = productVector;
    for (int i = 0; i < productVector.size(); ++i) {
        if (productVector[i].productStock == 0) {
            availableProducts.erase(availableProducts.begin() + i);
        } else {
            continue;
        }
    }
    std::cout << "====== Inventory ======" << std::endl;
    for (Product &product: availableProducts) {
        std::cout << product.productName << "   $" << product.productPrice << "    " << product.productStock << " left"
                  << std::endl;
    }
}

/*
 * addProductToCart function
 *
 * This function sees if the user puts in a product that is out of stock that might still be inside the productVector
 * and returns that it is out of stock. If not it will push the product that they want to purchase in the productCart vector.
 */

void ProductManager::addProductToCart(std::string availableProducts) {
    for (const Product &product: productVector) {
        if (product.productStock == 0) {
            std::cerr << product.productName << " is out of stock!" << std::endl;
            break;
        } else if (product.productName == availableProducts) {
            productCart.push_back(product);
        } else {
            continue;
        }
    }
}

/*
 * displayCart
 *
 * This function looks at the productCart vector and displays each item the user has chosen to possibly purchase and the total price
 * of everything they want
 */
void ProductManager::displayCart() {
    std::cout << "===== Cart =====" << std::endl;
    for (const Product &product: productCart) {
        std::cout << product.productName << " " << product.productPrice << std::endl;
    }

    std::cout << "================" << std::endl << "Total: $" << totalPriceOfCart();
}

/*
 * removeFromCart Fucntion
 *
 * This fuction takes a string of product that you want to remove from your cart and removes it from the productCart vector
 *
 */
void ProductManager::removeFromCart(std::string removedProduct) {
    for (int i = 0; i < productCart.size(); ++i) {
        if (productCart[i].productName == removedProduct) {
            productCart.erase(productCart.begin() + i);
            std::cout << "removed " << productCart[i].productName << " from cart" << std::endl;
            break;
        } else {
            continue;
        }
    }

}

/*
 * totalPriceOfCart Function
 *
 * This look are each price of each product in the productCart vector and adds it up to find the total of
 * everything combined.
 */
float ProductManager::totalPriceOfCart() {
    float total = 0;
    for (const Product &product: productCart) {
        total = total + std::stof(product.productPrice);
    }
    total = std::round(total * 100.f) / 100.f;
    return total;
}

/*
 * gatherCartIDs Function
 *
 * This function finds all id in each product in the productCart. Used to add to a transaction report.
 */
std::vector<int> ProductManager::gatherCartIDs() {
    std::vector<int> transactionIDs;
    for (const Product &purchase: productCart) {
        transactionIDs.push_back(purchase.productID);
    }
    return transactionIDs;
}

/*
 * setRewardPercent Function
 *
 * This function sets the reward percent this is already defined as a default 10%
 */
float ProductManager::setRewardPercent(float percent) {
    percent = percent / 100;
    rewardPercent = percent;
}

/*
 * purchase Function
 *
 * This looks at each product and subtracts one quantity from the products stock and saves the products updated info
 */
void ProductManager::purchase() {
    for (const Product &boughtProduct: productCart) {
        for (int i = 0; i < productVector.size(); ++i) {
            if (productVector[i].productName == boughtProduct.productName) {
                productVector[i].productStock--;
            } else {
                continue;
            }
        }
    }
    saveProducts();
}

/*
 * rewardPointsPurchase Function
 *
 * This function returns the amount of points left over after a purchase with reward points. Assuming that the manager
 * doesn't mind the lost of cents from purchasing with points.
 */

int ProductManager::rewardPointsPurchase(int customerRewardPts) {
    int total = totalPriceOfCart();
    int remainingPts;
    if (total > customerRewardPts) {
        std::cerr << "Not enough reward points!" << std::endl;
    } else {
        remainingPts = customerRewardPts - total;
        return remainingPts;
    }
}

/*
 * receivePoints Function
 *
 * This fucntion returns the integer of points that are awarded from a purchase
 */
int ProductManager::recivePoints() {
    int total = totalPriceOfCart();
    int points = total * rewardPercent;
    return points;
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
            product.productID = std::stoi(line.substr(TAB.length() + PRODID.length()));
            getline(infile, line);
            product.productName = line.substr(TAB.length() + PRODNAME.length());
            getline(infile, line);
            product.productPrice = line.substr(TAB.length() + PRODPRICE.length());
            getline(infile, line);
            product.productStock = std::stoi(line.substr(TAB.length() + PRODSTOCK.length()));
            tempProducts.push_back(product);
        }
    }

    productVector = tempProducts;
    infile.close();
}