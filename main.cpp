#include "CarRentalSystem.h"
#include <iostream>
#include <stdexcept>
#include <limits>

using namespace std;

string getCurrentDate()
{
    time_t t = time(nullptr);
    tm *local_time = localtime(&t);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d", local_time);
    return string(date);
}

bool isValidInteger(const string& str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}

void menu()
{
    CarRentalSystem rentalSystem;
    rentalSystem.readVehicleDetailsFromFile("dataset.txt");
    int choice;
    string licensePlate, name, licenseNumber, rentalDate, returnDate;
    do
    {
        cout << "\nCar Rental System Menu:" << endl;
        cout << "1. Rent a Vehicle" << endl;
        cout << "2. Return a Vehicle" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                rentalSystem.printAvailableVehicles();
                cout << "\nEnter vehicle license plate: ";
                cin >> licensePlate;
                if (licensePlate.empty())
                {
                    throw invalid_argument("License plate number cannot be empty.");
                }
                cout << "Enter customer name: ";
                cin >> name;
                if (cin.fail())
                {
                    throw invalid_argument("Customer name cannot be empty.");
                }
                cout << "Enter customer license number: ";
                cin >> licenseNumber;
                if (licenseNumber.empty())
                {
                    throw invalid_argument("License plate number cannot be empty.");
                }
                rentalDate = getCurrentDate();
                rentalSystem.rentVehicle(licensePlate, Customer(name, licenseNumber), rentalDate);
                break;
            case 2:
                cout << "\nEnter vehicle license plate: ";
                cin >> licensePlate;
                if (licensePlate.empty())
                {
                    throw invalid_argument("License plate number cannot be empty.");
                }
                returnDate = getCurrentDate();
                rentalSystem.returnVehicle(licensePlate, returnDate);
                break;
            case 3:
                cout << "Exiting program..." << endl;
                break;
            default:
                throw invalid_argument("Invalid choice. Please enter a number between 1 and 3.");
            }
        }
        catch (const exception &e)
        {
            cerr << "Exception: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (choice != 3);
}

void admin()
{
    CarRentalSystem rentalSystem;
    rentalSystem.readVehicleDetailsFromFile("dataset.txt");
    int choice;
    string make, model, licensePlate,yearStr;
    int year;
    double advance, price;

    do
    {
        cout << "\nCar Rental System Menu:" << endl;
        cout << "1. Add a Vehicle" << endl;
        cout << "2. Remove a Vehicle" << endl;
        cout << "3. Print Available Vehicles" << endl;
        cout << "4. Print Rented Vehicles" << endl;
        cout << "5. Print Rental Transactions" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        try
        {
            switch (choice)
            {
            case 1:
                cout << "Enter vehicle make: ";
                cin >> make;
                if (make.empty())
                {
                    throw invalid_argument("Vehicle make cannot be empty.");
                }
                cout << "Enter vehicle model: ";
                cin >> model;
                if (model.empty())
                {
                    throw invalid_argument("Vehicle model cannot be empty.");
                }
                cout << "Enter vehicle year: ";
                cin >> yearStr;
                if (!isValidInteger(yearStr))
                {
                    throw invalid_argument("Invalid year format. Please enter a valid integer.");
                }
                year = stoi(yearStr);
                cout << "Enter vehicle license plate: ";
                cin >> licensePlate;
                if (licensePlate.empty())
                {
                    throw invalid_argument("License plate number cannot be empty.");
                }
                cout << "Enter the Advance Amount: ";
                cin >> advance;
                if (cin.fail()||advance<100)
                {
                    throw invalid_argument("Invalid advance amount format. Please enter a valid number.");
                }
                cout << "Enter the Price per day : ";
                cin >> price;
                if (cin.fail()||advance<100)
                {
                    throw invalid_argument("Invalid price amount format. Please enter a valid number.");
                }
                rentalSystem.addVehicle(new Vehicle(make, model, year, licensePlate, advance, price));
                rentalSystem.appendVehicleToFile(*new Vehicle(make, model, year, licensePlate, advance, price));
                cout << "Vehicle added successfully." << endl;
                break;
            case 2:
                cout << "Enter license plate of the vehicle to remove: ";
                cin >> licensePlate;
                if (licensePlate.empty())
                {
                    throw invalid_argument("License plate number cannot be empty.");
                }
                rentalSystem.removeVehicle(licensePlate);
                break;
            case 3:
                rentalSystem.printAvailableVehicles();
                break;
            case 4:
                rentalSystem.printRentedVehicles();
                break;
            case 5:
                rentalSystem.printTransactionsFromFile("transactions.txt");
                break;
            case 6:
                cout << "Returning to..." << endl;
                break;
            default:
                throw invalid_argument("Invalid choice. Please enter a number between 1 and 5.");
            }
        }
        catch (const exception &e)
        {
            cerr << "Exception: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (choice != 6);
}

int main()
{
    CarRentalSystem rentalSystem;
    rentalSystem.readVehicleDetailsFromFile("dataset.txt");

    int choice;
    do
    {
        cout << "Car Rental Management System " << endl;
        cout << "1. Customer" << endl;
        cout << "2. Admin " << endl;
        cout << "3. Exit " << endl;
        cout << "Enter the the choice : ";
        cin >> choice;
        try
        {
            switch (choice)
            {
            case 1:
                menu();
                break;
            case 2:
                admin();
                break;
            case 3:
                cout << "Exiting program..." << endl;
                break;
            default:
                throw invalid_argument("Invalid choice. Please enter a number between 1 and 3.");
            }
        }
        catch (const exception &e)
        {
            cerr << "Exception: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    while (choice != 3);
    return 0;
}
