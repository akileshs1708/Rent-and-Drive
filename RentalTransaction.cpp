#include "RentalTransaction.h"
#include <iostream>
using namespace std;

RentalTransaction::RentalTransaction():Customer(),Vehicle(){
    rentalDate="";
    returnDate="";
}

RentalTransaction::RentalTransaction(const Customer& customer, const Vehicle& vehicle, string rentalDate): Customer(customer), Vehicle(vehicle), rentalDate(rentalDate) {}

void RentalTransaction::setReturnDate(string returnDate) {
    this->returnDate = returnDate;
}

string RentalTransaction::getRentalDate() const {
    return rentalDate;
}

string RentalTransaction::getReturnDate() const {
    return returnDate;
}
