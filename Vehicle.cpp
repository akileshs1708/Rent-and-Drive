#include "Vehicle.h"
using namespace std;

Vehicle::Vehicle(){
    make="";
    model="";
    year=0;
    licensePlate="";
    advance=0;
    totalPrice=0;
    available=0;
}

Vehicle::Vehicle(string make, string model, int year, string licensePlate, double advance, double totalPrice, bool available): make(make), model(model), year(year), licensePlate(licensePlate), available(available), advance(advance), totalPrice(totalPrice) {}

string Vehicle::getMake() const {
    return make;
}

string Vehicle::getModel() const {
    return model;
}

int Vehicle::getYear() const {
    return year;
}

string Vehicle::getLicensePlate() const {
    return licensePlate;
}

bool Vehicle::isAvailable() const {
    return available;
}

double Vehicle::getAdvance() const {
    return advance;
}

double Vehicle::getTotalPrice() const {
    return totalPrice;
}

void Vehicle::rentVehicle() {
    available = 0;
}

void Vehicle::returnVehicle() {
    available = 1;
}
