#include "../src/ExcelHelper.hpp"
#include "../src/Management.hpp"
#include "../src/ExcelHelper.hpp"
#include "../src/Employee.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <map>

void testAddEmployee(){
    Management::addEmployee();
}

void testGetEmployees(){
    std::vector<Employee> list = Management::getEmployees();

    // assert(list.size() == 10);
    for(auto emp: list){
        std::cout << emp.name << std::endl;
    }
}

void testGenerateRoster(){
    std::vector<Employee> list = Management::getEmployees();

    std::map<int, std::vector<std::string>> roster = Management::generateRoster(list);
    
    for(auto [day, shifts] : roster){
        std::cout << "Day " << day + 1 << std::endl;
        for(auto shift : shifts){
            std::cout << shift << std::endl;
        }
    }
}

int main(){
    // testGetEmployees();
    testGenerateRoster();
    std::cout << "Tests successful" << std::endl;
}