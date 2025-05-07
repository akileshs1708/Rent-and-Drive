#include "Customer.h"
using namespace std;

Customer::Customer(){
    name="";
    licenseNumber="";
}

Customer::Customer(string name, string licenseNumber): name(name), licenseNumber(licenseNumber) {}

string Customer::getName() const {
    return name;
}

string Customer::getLicenseNumber() const {
    return licenseNumber;
}
