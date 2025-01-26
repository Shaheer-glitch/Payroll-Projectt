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
