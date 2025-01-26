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

