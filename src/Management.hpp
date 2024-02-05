#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <string>
#include "Employee.hpp"
#include "ExcelHelper.hpp"

class Management{
    public:
    static void addEmployee();
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
#endif