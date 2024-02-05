#include "../src/ExcelHelper.hpp"
#include "../src/Management.hpp"
#include "../src/ExcelHelper.hpp"
#include <iostream>
#include <cassert>
#include <string>

void testAddEmployee(){
    Management::addEmployee();
}

int main(){
    testAddEmployee();

    std::cout << "Tests successful";
}