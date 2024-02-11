#include <iostream>
#include "Management.hpp"
using namespace std;

void displayMenu(){
    cout << "Employee Management System" << std::endl;
    cout << "(1) Add Employee" << std::endl;
    cout << "(2) Remove Employee" << std::endl;
    cout << "(3) Get employees" << std::endl;
    cout << "(4) Generate Weekly Roster" << std::endl;
    cout << "(5) Email roster to Employees" << std::endl;
    cout << "(6) Exit" << std::endl;
    cout << "Select an option: ";
}

int main() {
    int option;
    while(true){
        displayMenu();
        cin >> option;
        switch(option){
            case 1:
                Management::addEmployee();
                break;
            case 2:
                Management::removeEmployee();
                break;
            case 3:
                {
                    std::vector<Employee> employees = Management::getEmployees();
                    for(auto e: employees) cout << e.name << endl;
                }
                break;
            case 4:
                {
                    std::vector<Employee> employees = Management::getEmployees();
                    Management::generateRoster(employees);
                }
                break;
            case 5:
                {
                    std::set<std::string> emails = ExcelHelper::getEmails("../src/employees.csv");
                    Management::sendEmails(emails);
                }
                break;
            case 6:
                std::cout << "Exiting..." << std::endl;
                return 0;
            default:
                std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
    return 0;
}