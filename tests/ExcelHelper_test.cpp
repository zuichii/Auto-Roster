#include "../src/ExcelHelper.hpp"
#include <iostream>
#include <cassert>
#include <string>

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

int main(){
    test_readExcel();
    test_generateId();
}