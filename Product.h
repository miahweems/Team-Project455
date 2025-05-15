#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    int productID;       // Unique ID for the product
    std::string productName;     // Name or description of the product
    std::string productPrice;   // Price of the product
    int productStock = 0;        // Number of items available in stock
};

#endif
