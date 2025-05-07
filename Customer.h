#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
using namespace std;

class Customer {
protected:
    string name;
    string licenseNumber;

public:
    Customer();
    Customer(string name, string licenseNumber);
    string getName() const;
    string getLicenseNumber() const;
};

#endif // CUSTOMER_H
