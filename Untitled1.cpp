#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept> // For runtime_error
using namespace std;

// Employee structure
struct Employee {
    int id;
    string name;
    float hoursWorked;
    float hourlyRate;
    float salary;
    float deduction;  // Text Deduction (e.g., tax, insurance, etc.)
    float bonus;      // Bonus
};

// Function prototypes
void addEmployee();
void viewEmployees();
void searchEmployeeByID();
void deleteEmployeeByID();
void updateEmployeeByID();
float calculateSalary(float hoursWorked, float hourlyRate, float deduction, float bonus);

int main() {
    int choice;

    do {
        cout << "\n========== Payroll System ==========" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View Employees" << endl;
        cout << "3. Search Employee by ID" << endl;
        cout << "4. Delete Employee by ID" << endl;
        cout << "5. Update Employee Details" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        
          // Validate user input
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            continue;
        }
        
        switch (choice) {
        case 1:
            addEmployee();
            break;
        case 2:
            viewEmployees();
            break;
        case 3:
            searchEmployeeByID();
            break;
        case 4:
            deleteEmployeeByID();
            break;
        case 5:
            updateEmployeeByID();
            break;
        case 6:
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
