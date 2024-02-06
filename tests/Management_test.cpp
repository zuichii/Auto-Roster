#include "../src/ExcelHelper.hpp"
#include "../src/Management.hpp"
#include "../src/ExcelHelper.hpp"
#include "../src/Employee.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <vector>

void testAddEmployee(){
    Management::addEmployee();
}

void testGetEmployees(){
    std::vector<Employee> list = Management::getEmployees();

    assert(list.size() == 10);
    for(auto emp: list){
        std::cout << emp.name << std::endl;
    }
}

int main(){
    testGetEmployees();
    std::cout << "Tests successful";
}