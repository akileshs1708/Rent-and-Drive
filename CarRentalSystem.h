#ifndef CARRENTALSYSTEM_H
#define CARRENTALSYSTEM_H

#include "Vehicle.h"
#include "Customer.h"
#include "RentalTransaction.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>
#include <cmath>
#include <sstream>
using namespace std;

class CarRentalSystem {
private:
    vector<Vehicle*> vehicles;
    vector<RentalTransaction> transactions;

public:
    void addVehicle(Vehicle* vehicle);
    void rentVehicle(const string& licensePlate, const Customer& customer, string rentalDate);
    void removeVehicle(const string& licensePlate);
    void returnVehicle(const string& licensePlate, string returnDate);
    void updateAvailabilityInFile(const string& licensePlate, int availability);
    tm parseDate(const string& dateStr);
    double calculateRentalDuration(const string& rentalDate, const string& returnDate);
    double calculateTotalBill(const Vehicle& vehicle, double rentalDuration);
    void printAvailableVehicles() const;
    void printRentedVehicles() const;
    void printTransactions() const;
    void readVehicleDetailsFromFile(const string& filename);
    void readTransactionsFromFile(const string& filename);
    void removeVehicleFromFile(const string& licensePlate);
    void appendVehicleToFile(const Vehicle& vehicle);
    void appendTransactionToFile(const RentalTransaction& transaction);
    void printTransactionsFromFile(const string& filename);
};

#endif // CARRENTALSYSTEM_H
