#ifndef  BOOLS_H
#define BOOLS_H

#include <string>
#include <cctype>


/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's first and last name
        follow the specification requirements
*/
bool isValidName(const std::string &name) {
    if (name.length() > 12 || name.length() < 1) {
        return false;
    } else {
        for (char c : name) {
            if (!std::isalpha(c)) {
                return false;
            } else {
                continue;
            }
        }
        return true;
    }
}
/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's username
        follows the specification requirements
*/
bool isValidUsername(const std::string &username) {
    if (username.length() > 10 || username[0] != 'U' || username[1] != '_') {
        return false;
    } else {
        int digitCount = 0;
        for (int i = 2; i < username.length() && std::isdigit(username[i]); i++) {
            digitCount++;
            if (digitCount > 3) {
                return false;
            } else {
                continue;
            }
        }
        return true;
    }
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's age
        follows the specification requirements
*/
bool isValidAge(const std::string &ageStr) {
    if (ageStr.empty() || ageStr[0] == '0') {
        return false;
    } else {
        int age = std::stoi(ageStr);
        if (age >= 18 && age <= 100) {
            return true;
        } else {
            return false;
        }
    }
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's credit card number
        follows the specification requirements
*/
bool isValidCreditCard(const std::string &cardNumber) {
    if (cardNumber.length() != 14) {
        return false;
    } else {
        if (cardNumber[0] == '0') {
            return false;
        } else {
            for (int i = 0; i < cardNumber.length(); i++) {
                if (i == 4 || i == 9) {
                    if (cardNumber[i] != '-') {
                        return false;
                    } else {
                        continue;
                    }
                } else {
                    if (!std::isdigit(cardNumber[i])) {
                        return false;
                    } else {
                        continue;
                    }
                }
            }
            return true;
        }
    }
}

/* Return Type: Boolean
   Input Parameter: int
   Use: This function is used to validate whether the number 
        under consideration is positive
*/
bool isPositive(int num) {
    if (num > 0) {
        return true;
    } else {
        return false;
    }
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate user's entrance for price
   in the command line interface.
*/
bool isValidProductPrice(const std::string &price) {

    bool decimalFound = false;
    int decimalCount = 0; //counts digits after decimal encountered
    if (!std::isdigit(price[0])) {
        return false;      //checks that amount starts with a num ie: non negative
    }

    else {

        for (int i = 1; i < price.length(); i++) {
            if (std::isdigit(price[i])) {
                if (decimalFound){
                    ++decimalCount;
                }
                else {
                continue; //checks if digit
                }
            }
            else if (price[i] == '.' && !decimalFound) {
                decimalFound = true;  //blocks user from using more than one decimal
            }
            else {
                return false;
            }
        }
    }
    return !decimalFound || decimalCount <= 2;
}

#endif