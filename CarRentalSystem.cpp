#include "CarRentalSystem.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cmath>
using namespace std;

vector<string> split(const string& s, char delimiter)
{
    vector<string> tokens;
    stringstream ss(s);
    string token;
    while (getline(ss, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

void CarRentalSystem::addVehicle(Vehicle* vehicle)
{
    vehicles.push_back(vehicle);
}

void CarRentalSystem::rentVehicle(const string& licensePlate, const Customer& customer, string rentalDate)
{
    for (auto& vehicle : vehicles)
    {
        if (vehicle->getLicensePlate() == licensePlate)
        {
            if (vehicle->isAvailable())
            {
                vehicle->rentVehicle();
                transactions.push_back(RentalTransaction(customer, *vehicle, rentalDate));
                updateAvailabilityInFile(licensePlate, 0);
                cout <<"Advance to be Paid : " <<vehicle->getAdvance()<<endl;
                cout << "Vehicle with license plate " << licensePlate << " rented successfully." << endl;
            }
            else
            {
                cout << "Vehicle with license plate " << licensePlate << " is not available for rent." << endl;
            }
            return;
        }
    }
    cout << "Vehicle with license plate " << licensePlate << " not found." << endl;
}

void CarRentalSystem::removeVehicle(const string& licensePlate)
{
    for (auto& vehicle : vehicles)
    {
        if (vehicle->getLicensePlate() == licensePlate)
        {
            removeVehicleFromFile(licensePlate);
            cout << "Vehicle with license plate " << licensePlate << " removed from system." << endl;
            delete vehicle;
            vehicle = nullptr;
            return;
        }
    }
    cout << "Vehicle with license plate " << licensePlate << " not found in the system." << endl;
}

void CarRentalSystem::returnVehicle(const string& licensePlate, string returnDate)
{
    double rentalDuration, totalBill;
    for (auto& vehicle : vehicles)
    {
        if (vehicle->getLicensePlate() == licensePlate)
        {
            if (!vehicle->isAvailable())
            {
                vehicle->returnVehicle();
                for (auto& transaction : transactions)
                {
                    if (transaction.getLicensePlate() == licensePlate && transaction.getReturnDate().empty())
                    {
                        transaction.setReturnDate(returnDate);
                        rentalDuration = calculateRentalDuration(transaction.getRentalDate(), returnDate);
                        totalBill = calculateTotalBill(*vehicle, rentalDuration);
                        appendTransactionToFile(transaction);
                        break;
                    }
                }
                updateAvailabilityInFile(licensePlate, 1);
                cout << "Vehicle with license plate " << licensePlate << " returned successfully." << endl;
                cout << "Rental Summary:" << endl;
                cout << "Make: " << vehicle->getMake() << ", Model: " << vehicle->getModel() << endl;
                cout << "Rental Date: " << ", Return Date: " << returnDate << endl;
                cout << "Rental Duration: " << rentalDuration << " days" << endl;
                cout << "Total Bill: Rs. " << totalBill << endl;
            }
            else
            {
                cout << "Vehicle with license plate " << licensePlate << " is already available." << endl;
            }
            return;
        }
    }
    cout << "Vehicle with license plate " << licensePlate << " not found." << endl;
}

void CarRentalSystem::updateAvailabilityInFile(const string& licensePlate, int availability)
{
    ifstream inFile("dataset.txt");
    ofstream outFile("temp.txt");

    if (!inFile || !outFile)
    {
        cerr << "Error: Unable to open files." << endl;
        return;
    }
    string line;
    while (getline(inFile, line))
    {
        if (line.find(licensePlate) != string::npos)
        {
            size_t pos = line.find_last_of(',');
            line.replace(pos + 1, 1, to_string(availability));
        }
        outFile << line << endl;
    }
    inFile.close();
    outFile.close();
    remove("dataset.txt");
    rename("temp.txt", "dataset.txt");
}

tm CarRentalSystem::parseDate(const string& dateStr)
{
    tm time = {};
    istringstream ss(dateStr);
    ss >> time.tm_year;
    ss.ignore();
    ss >> time.tm_mon;
    ss.ignore();
    ss >> time.tm_mday;
    time.tm_year -= 1900;
    time.tm_mon -= 1;
    return time;
}

double CarRentalSystem::calculateRentalDuration(const string& rentalDate, const string& returnDate)
{
    tm rentalTime = parseDate(rentalDate);
    tm returnTime = parseDate(returnDate);
    time_t rentalTimestamp = mktime(&rentalTime);
    time_t returnTimestamp = mktime(&returnTime);
    time_t difference = difftime(returnTimestamp, rentalTimestamp);
    double days = abs(difference) / (24 * 60 * 60);
    return days;
}

double CarRentalSystem::calculateTotalBill(const Vehicle& vehicle, double rentalDuration)
{
    double rentalRate = vehicle.getTotalPrice();
    double totalBill = rentalRate * rentalDuration + vehicle.getAdvance();
    return totalBill;
}

void CarRentalSystem::printAvailableVehicles() const
{
    cout << "Available Vehicles:" << endl;
    for (const auto& vehicle : vehicles)
    {
        if (vehicle->isAvailable())
        {
            cout << vehicle->getMake() << " " << vehicle->getModel() << " (" << vehicle->getYear() << "), License Plate: " << vehicle->getLicensePlate() << endl;
        }
    }
}

void CarRentalSystem::printRentedVehicles() const
{
    cout << "Rented Vehicles: " << endl;
    for (const auto& vehicle : vehicles)
    {
        if (!vehicle->isAvailable())
        {
            cout << "Make: " << vehicle->getMake() << ", Model: " << vehicle->getModel() << " (" << vehicle->getYear() << "), License Plate: " << vehicle->getLicensePlate() << endl;
            for (const auto& transaction : transactions)
            {
                if (transaction.getLicensePlate() == vehicle->getLicensePlate())
                {
                    cout << "  - Rented by: " << transaction.getName() << " (License Number: " << transaction.getLicenseNumber() << ")" << endl;
                }
            }
        }
    }
}

void CarRentalSystem::printTransactions() const
{
    cout << "Rental Transactions:" << endl;
    for (const auto& transaction : transactions)
    {
        cout << "Customer: " << transaction.getName() << ", Vehicle: " << transaction.getMake() << " " << transaction.getModel()
             << ", Rental Date: " << transaction.getRentalDate() << ", Return Date: " << transaction.getReturnDate() << endl;
    }
}

void CarRentalSystem::readVehicleDetailsFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            vector<string> parts = split(line, ',');
            if (parts.size() == 7)
            {
                string make = parts[0];
                string model = parts[1];
                int year = stoi(parts[2]);
                string licensePlate = parts[3];
                double advance = stod(parts[4]);
                double price = stod(parts[5]);
                bool available = (bool)stoi(parts[6]);
                addVehicle(new Vehicle(make, model, year, licensePlate, advance, price, available));
            }
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open file." << endl;
        exit(1);
    }
}

void CarRentalSystem::readTransactionsFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        cout << "Transaction Details:" << endl;
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open " << filename << " for reading." << endl;
    }
}

void CarRentalSystem::removeVehicleFromFile(const string& licensePlate)
{
    ifstream inFile("dataset.txt");
    ofstream outFile("temp.txt");

    if (!inFile || !outFile)
    {
        cerr << "Error: Unable to open files." << endl;
        return;
    }
    string line;
    while (getline(inFile, line))
    {
        if (line.find(licensePlate) == string::npos)
        {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();
    remove("dataset.txt");
    rename("temp.txt", "dataset.txt");
}

void CarRentalSystem::appendVehicleToFile(const Vehicle& vehicle)
{
    ofstream file("dataset.txt", ios::app);
    if (file.is_open())
    {
        file << vehicle.getMake() << "," << vehicle.getModel() << "," << vehicle.getYear() << "," << vehicle.getLicensePlate() << "," << vehicle.isAvailable() << endl;
        file.close();
        cout << "Vehicle details added .. " << endl;
    }
    else
    {
        cerr << "Unable to open vehicles.txt for appending." << endl;
    }
}

void CarRentalSystem::appendTransactionToFile(const RentalTransaction& transaction)
{
    ofstream file("transactions.txt", ios::app);
    if (file.is_open())
    {
        file << "Make: " << transaction.getMake() << ", Model: " << transaction.getModel() << ", Year: " << transaction.getYear() << endl;
        file << "License Plate: " << transaction.getLicensePlate() << ", Rental Date: " << transaction.getRentalDate();
        file << ", Return Date: " << transaction.getReturnDate() << endl;
        file << "Customer Name: " << transaction.getName() << ", License Number: " << transaction.getLicenseNumber() << endl;
        file << "-------------------------" << endl;
        file.close();
        cout << "Transaction details added to file." << endl;
    }
    else
    {
        cerr << "Unable to open transactions.txt for appending." << endl;
    }
}

void CarRentalSystem::printTransactionsFromFile(const string& filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        cout << "Transaction Details:" << endl;
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Unable to open " << filename << " for reading." << endl;
    }
}
