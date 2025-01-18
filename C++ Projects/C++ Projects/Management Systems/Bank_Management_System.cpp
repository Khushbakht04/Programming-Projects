#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Customer {
public:
    int id;
    string name;
    float balance;
    float money;

public:
    // Constructor to initialize the customer object with id, name, and balance
    Customer(int i, string n, float b) {
        id = i;
        name = n;
        balance = b;
    }

    // Default constructor to initialize with default values
    Customer() {
        id = 0;
        name = "Unknown";
        balance = 0.0;
    }

    // Method to add customer details to a file
    int addCustomer() {
        ofstream outfile("Customer.txt", ios::app);

        if (!outfile) {
            cerr << "File could not be opened for writing!" << endl;
            return 1;
        }

        outfile << "Customer Name: " << name << endl;
        outfile << "Customer Id: " << id << endl;
        outfile << "Customer balance: " << balance << endl;
        outfile << "-----------------------------------" << endl;

        outfile.close();
        return 0;
    }

    // Method to find and display customer details from the file by ID
    int findCustomer(int searchId) {
        ifstream infile("Customer.txt");

        if (!infile) {
            cerr << "File could not be opened for reading!" << endl;
            return 1;
        }

        bool found = false;
        string line;
        while (getline(infile, line)) {
            if (line.find("Customer Id: " + to_string(searchId)) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Customer with ID " << searchId << " not found." << endl;
        }

        infile.close();
        return 0;
    }

    // Method to withdraw a specified amount from the balance
    void withdraw() {
        cout << "Enter the amount you want to withdraw: ";
        cin >> money;
        if (balance >= money) {
            balance -= money;
            cout << "Withdrawn " << money << ". Current balance: " << balance << endl;
        } else {
            cout << "Insufficient balance." << endl;
        }
    }

    // Method to deposit a specified amount into the balance
    void deposit() {
        cout << "Enter the amount you want to deposit: ";
        cin >> money;
        balance += money;
        cout << "Deposited " << money << ". Current balance: " << balance << endl;
    }

    // Method to display the current balance
    void displayDetails() {
        cout << "Your current balance is: " << balance << endl;
    }
};

int main() {
    int choice;
    string name;
    int id;
    float balance;

    // Prompt user for initial customer details
    cout << "-------- Bank Management System --------" << endl;
    cout << "Enter the following details:" << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "ID: ";
    cin >> id;
    cout << "Balance: ";
    cin >> balance;

    Customer cus(id, name, balance);

    do {
        // Menu for user to choose actions
        cout << "\nSelect one of these: " << endl;
        cout << "1. Add Customer" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Check Balance" << endl;
        cout << "5. Find Customer by ID" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cus.addCustomer();
                break;
            case 2:
                cus.deposit();
                break;
            case 3:
                cus.withdraw();
                break;
            case 4:
                cus.displayDetails();
                break;
            case 5:
                {
                    int searchId;
                    cout << "Enter Customer ID to find: ";
                    cin >> searchId;
                    cus.findCustomer(searchId);
                    break;
                }
            case 6:
                cout << "Exiting... Thank you!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
