#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

struct Product {
    std::string productID;       // Unique ID for the product
    std::string productName;     // Name or description of the product
    float productPrice = 0.0f;   // Price of the product
    int productStock = 0;        // Number of items available in stock
};

#endif
