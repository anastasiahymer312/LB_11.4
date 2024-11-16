#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void DisplayMenu();
void CreateCarFile(const string& filename);
void UpdateFileWithMaxPrice(const string& filename);

int main() {

    int option;
    string filename; 

    while (true) {
        DisplayMenu();
        cout << "Select an option: ";
        if (!(cin >> option)) {
            cout << "Invalid value! Please enter a number\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (option == 0) break;

        switch (option) {
        case 1:
            cout << "Enter a file name to save car data: ";
            cin >> filename;
            CreateCarFile(filename);
            break;
        case 2:
            cout << "Enter the name of the car data file: ";
            cin >> filename;
            UpdateFileWithMaxPrice(filename);
            break;
        default:
            cout << "Wrong choice. Try again.\n";
        }
    }

    return 0;
}

void DisplayMenu() {
    cout << "\nMenu:\n";
    cout << "1 - Create a car data file\n";
    cout << "2 -Update the file with the maximum price for each firm\n";
    cout << "0 - Exit\n";
}

void CreateCarFile(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Could not open file for writing!\n";
        return;
    }

    string company, model;
    double price;
    char another;

    do {
        cout << "Enter the name of the company: ";
        cin >> ws;
        getline(cin, company);
        cout << "Enter the make of the car : ";
        getline(cin, model);
        cout << "Enter the price of the car: ";
        while (!(cin >> price)) {
            cout << "Incorrect value! Enter a number for the price.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        file << company << " " << model << " " << price << "\n";

        cout << "Add another car? (y/n): ";
        cin >> another;
    } while (another == 'y' || another == 'Y');

    file.close();
    cout << "Data saved to file successfully " << filename << ".\n";
}

void UpdateFileWithMaxPrice(const string& filename) {
    ifstream infile(filename);
    ofstream temp("temp.txt");

    if (!infile.is_open() || !temp.is_open()) {
        cout << "Failed to open file!\n";
        return;
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string company, model;
        double price, max_price = 0;

        iss >> company;
        while (iss >> model >> price) {
            if (price > max_price) {
                max_price = price;
            }
        }
        temp << line << " Maximum price: " << max_price << "\n";
    }

    infile.close();
    temp.close();

    remove(filename.c_str());
    rename("temp.txt", filename.c_str());

    cout << "The file has been updated with the maximum price for each firm.\n";
}
