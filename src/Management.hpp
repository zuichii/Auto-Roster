#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include "Employee.hpp"
#include "ExcelHelper.hpp"

class Management{
    public:
    static void addEmployee();
    static std::vector<Employee> getEmployees();
};

void Management::addEmployee(){
    int id = ExcelHelper::generateId("../tests/test_employees.csv");
    std::string name, email;
    bool morning, afternoon, evening, softgoods, hardgoods, checkouts, customer_service, nightfill;

    std::cout << "Enter employee name: " << std::endl;
    std::cin >> name;

    std::cout << "Enter employee email: " << std::endl;
    std::cin >> email;
    
    std::cout << "Enter employee morning availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> morning;
    std::cin.ignore(); 

    std::cout << "Enter employee afternoon availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> afternoon;
    std::cin.ignore(); 

    std::cout << "Enter employee evening availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> evening;
    std::cin.ignore(); 

    std::cout << "Enter employee softgoods preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> softgoods;
    std::cin.ignore(); 

    std::cout << "Enter employee hardgoods preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> hardgoods;
    std::cin.ignore(); 

    std::cout << "Enter employee checkouts preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> checkouts;
    std::cin.ignore(); 

    std::cout << "Enter employee customer service preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> customer_service;
    std::cin.ignore(); 

    std::cout << "Enter employee nightfill preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> nightfill;
    std::cin.ignore(); 

    Employee emp(id, name, email, morning, afternoon, evening, softgoods, hardgoods, checkouts, customer_service, nightfill);
    ExcelHelper::writeExcel(emp, "../tests/test_employees.csv");
}

std::vector<Employee> Management::getEmployees(){
    std::vector<std::vector<std::string>> data = ExcelHelper::readExcel("../tests/test_employees.csv");
    std::vector<Employee> list;
    for(int i = 0; i < 10; i++){
        std::vector<std::string> row = data[i];

        int id = std::stoi(row[0]);
        std::string name = row[1];
        std::string email = row[2];
        bool morning = (row[3] == "true");
        bool afternoon = (row[4] == "true");
        bool evening = (row[5] == "true");
        bool softgoods = (row[6] == "true");
        bool hardgoods = (row[7] == "true");
        bool checkouts = (row[8] == "true");
        bool customerService = (row[9] == "true");
        bool nightfill = (row[10] == "true");

        Employee emp(id, name, email, morning, afternoon, evening, softgoods, hardgoods, checkouts, customerService, nightfill);
        list.push_back(emp);
    }
    return list;
}
#endif