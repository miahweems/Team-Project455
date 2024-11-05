#include <string>
#include <cctype>

using namespace std;

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's first and last name
        follow the specification requirements
*/
bool isValidName(const string &name) {
    
    if (name.length() > 12) {
        return false;
    }

    for (char c : name) {
        if (!isalpha(c)) {
            return false;
        }
    }
    
    return true;
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's username
        follows the specification requirements
*/
bool isValidUsername(const string &username) {

    if (username.length() < 10 || username[0] != 'U' || username[1] != '_') {

        return false;    //shorter than 10 or doesnt begin with U_
    }
    
    int digitCount = 0;

    for (int i = 2; i < username.length() && isdigit(username[i]); i++) {
        
        digitCount++;
        
        if (digitCount > 3) {
            return false;    //more than 3 digits
        }
    }
    
    return true;
}


/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's age
        follows the specification requirements
*/
bool isValidAge(const string &ageStr) {

    if (ageStr.empty() || ageStr[0] == '0') {
        return false;            //cant start with zero
    }

    int age = stoi(ageStr);

    return age >= 18 && age <= 100;  //return true if between 18 and 100
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's credit card number
       follows the specification requirements
*/
bool isValidCreditCard(const string &cardNumber) {

    if (cardNumber.length() != 14) {
        return false;                 //not valid length
    }

    if (cardNumber[0] == '0') {
        return false;   //cant start with 0
    }

    for (int i = 0; i < cardNumber.length(); i++) {

        if (i == 4 || i == 9) {
            
            if (cardNumber[i] != '-') {
                return false;             // xxxx-xxxx-xxxx
            }

        } else {
            if (!isdigit(cardNumber[i])) { //must be nums
                return false;
            }   
        }
    }
    return true;
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the system's customer ID
       follows the specification requirements
*/
bool isValidCustID(const string &custID) {

    if (custID.substr(0, 6) != "CustID" || custID.length() != 16) {
        return false;
    }

    for (int i = 6; i < custID.length(); i++) {
        
        if (!isdigit(custID[i])) {
            return false;
        }
    }

    return true;
}

/* Return Type: Boolean
   Input Parameter: string
   Use: This function is used to validate whether the user's Product ID
       follows the specification requirements
*/
bool isValidProductID(const string &prodID) {

    if (prodID.substr(0,4) != "Prod" || prodID.length() != 9) {
        return false;
    }

    for (int i = 4; i < prodID.length(); i++) {

        if (!isdigit(prodID[i])) {
            return false;
        }
    }

    return true;
}

/* Return Type: Boolean
   Input Parameter: int
   Use: This function is used to validate whether the number 
       under consideration is positive
*/
bool isPositive(int num) {
    return num > 0;
}