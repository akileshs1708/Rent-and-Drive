#ifndef RENTALTRANSACTION_H
#define RENTALTRANSACTION_H

#include "Customer.h"
#include "Vehicle.h"
#include <string>
using namespace std;

class RentalTransaction : public Customer, public Vehicle {
private:
    string rentalDate;
    string returnDate;

public:
    RentalTransaction();
    RentalTransaction(const Customer& customer, const Vehicle& vehicle, string rentalDate);
    void setReturnDate(string returnDate);
    string getRentalDate() const;
    string getReturnDate() const;
};

#endif // RENTALTRANSACTION_H
