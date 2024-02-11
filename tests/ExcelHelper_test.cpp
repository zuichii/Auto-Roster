#include "../src/ExcelHelper.hpp"
#include "../src/Management.hpp"
#include <iostream>
#include <cassert>
#include <string>
#include <set>

void test_generateId(){
    std::string filePath = "test_employees.csv";
    int id = ExcelHelper::generateId(filePath);
    assert(id == 11);
    std::cout << "Generated ID: " << id << std::endl;
}

void test_readExcel(){
    std::string filePath = "test_employees.csv";
    std::vector<std::vector<std::string>> data = ExcelHelper::readExcel(filePath);

    assert(data.size() == 10); 
   
    for(std::vector<std::string> row: data){
        for(int i = 0; i < row.size(); i++){
            std::cout << row[i];
            if(i < row.size()-1) std::cout << ',';
        }
        std::cout << std::endl;
    }
}

void test_createCSV(){
    std::vector<Employee> list = Management::getEmployees();
    
    std::map<int, std::vector<std::string>> roster = Management::generateRoster(list);

    ExcelHelper::createCSV(roster);
}

void test_getEmails(){
    std::set<std::string> email_list;
    
    email_list = ExcelHelper::getEmails("test_roster.csv");

    for(auto email : email_list) std::cout << email << std::endl;
}

void test_removeEmployee(){
    ExcelHelper::removeEmployeeByID("test_employees.csv", 5);
}


int main(){
    // test_readExcel();
    // test_generateId();
    // test_createCSV();
    // test_getEmails();
    test_removeEmployee();
    std::cout << "All tests passed!" << std::endl;
}