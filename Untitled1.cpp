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

// Function to calculate salary with deductions and bonus
float calculateSalary(float hoursWorked, float hourlyRate, float deduction, float bonus) {
    return (hoursWorked * hourlyRate) - deduction + bonus;
    
    // Function to add an employee
void addEmployee() {
    ofstream outFile;

    // Open the file for appending
    outFile.open("employees.txt", ios::app);

    // Check if file is opened successfully
    if (!outFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Employee emp;
    cout << "\nEnter Employee ID: ";
    cin >> emp.id;

    cin.ignore(); // Clear the buffer
    cout << "Enter Employee Name: ";
    getline(cin, emp.name);

    cout << "Enter Hours Worked: ";
    cin >> emp.hoursWorked;

    cout << "Enter Hourly Rate: $ ";
    cin >> emp.hourlyRate;

    cout << "Enter Deduction (e.g., tax or insurance): $ ";
    cin >> emp.deduction;

    cout << "Enter Bonus: $ ";
    cin >> emp.bonus;

    emp.salary = calculateSalary(emp.hoursWorked, emp.hourlyRate, emp.deduction, emp.bonus);

    // Write to file
    outFile << emp.id << "," << emp.name << "," << emp.hoursWorked << "," << emp.hourlyRate << "," 
            << emp.deduction << "," << emp.bonus << "," << emp.salary << endl;

    cout << "Employee added successfully!" << endl;
    outFile.close();
}
// Function to view all employees
void viewEmployees() {
    ifstream inFile;

    // Open the file for reading
    inFile.open("employees.txt");

    // Check if file is opened successfully
    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    Employee emp;
    string line;

    cout << "\n========== Employee Records ==========" << endl;
    cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Hours Worked" << setw(15) << "Hourly Rate"
         << setw(15) << "Deduction" << setw(15) << "Bonus" << setw(15) << "Salary" << endl;
    cout << "-------------------------------------------------------------------------------" << endl;

    while (getline(inFile, line)) {
        size_t pos = 0;
        string token;
        int column = 0;

        // Parse the line
        while ((pos = line.find(',')) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + 1);  // Erase the processed token from the line

            stringstream ss(token);
            switch (column) {
            case 0:
                ss >> emp.id; // Manually convert to integer using stringstream
                break;
            case 1:
                emp.name = token;
                break;
            case 2:
                ss >> emp.hoursWorked; // Manually convert to float using stringstream
                break;
            case 3:
                ss >> emp.hourlyRate; // Manually convert to float using stringstream
                break;
            case 4:
                ss >> emp.deduction; // Deduction
                break;
            case 5:
                ss >> emp.bonus; // Bonus
                break;
            }
            column++;
        }

        // The last part of the line is the salary
        stringstream ss(line);
        ss >> emp.salary; // Convert the remaining line to salary

        cout << left << setw(10) << emp.id << setw(20) << emp.name << setw(15) << emp.hoursWorked << "$"<< setw(15) << emp.hourlyRate
             << "$"<< setw(15) << emp.deduction << "$"<< setw(15) << emp.bonus << "$"<< setw(15) << emp.salary << endl;
    }

    inFile.close();
}

// Function to search for an employee by ID
void searchEmployeeByID() {
    ifstream inFile("employees.txt");

    if (!inFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    int searchID;
    cout << "Enter Employee ID to search: ";
    cin >> searchID;

    Employee emp;
    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        stringstream tokenStream(token);
        tokenStream >> emp.id;

        if (emp.id == searchID) {
            getline(ss, emp.name, ',');
            ss >> emp.hoursWorked >> emp.hourlyRate >> emp.deduction >> emp.bonus >> emp.salary;
            cout << "\nEmployee Found:" << endl;
            cout << "ID: " << emp.id << ", Name: " << emp.name << ", Hours Worked: " << emp.hoursWorked
                 << ", Hourly Rate: " << emp.hourlyRate << ", Deduction: " << emp.deduction 
                 << ", Bonus: " << emp.bonus << ", Salary: " << emp.salary << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Employee with ID " << searchID << " not found." << endl;
    }

    inFile.close();
}

// Function to delete an employee by ID
void deleteEmployeeByID() {
    ifstream inFile("employees.txt");
    ofstream outFile("temp.txt");

    if (!inFile || !outFile) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    int deleteID;
    cout << "Enter Employee ID to delete: ";
    cin >> deleteID;

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        stringstream tokenStream(token);
        int id;
        tokenStream >> id;

        if (id == deleteID) {
            found = true;
            continue; // Skip this employee
        }

        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    remove("employees.txt");
    rename("temp.txt", "employees.txt");

    if (found) {
        cout << "Employee with ID " << deleteID << " has been deleted." << endl;
    } else {
        cout << "Employee with ID " << deleteID << " not found." << endl;
    }
}
