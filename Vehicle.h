#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>

using namespace std;

class Vehicle {
protected:
    string make;
    string model;
    int year;
    string licensePlate;
    double advance;
    double totalPrice;
    bool available;

public:
    Vehicle();
    Vehicle(string make, string model, int year, string licensePlate, double advance, double totalPrice, bool available = 1);
    string getMake() const;
    string getModel() const;
    int getYear() const;
    string getLicensePlate() const;
    bool isAvailable() const;
    double getAdvance() const;
    double getTotalPrice() const;
    void rentVehicle();
    void returnVehicle();
};

#endif // VEHICLE_H
