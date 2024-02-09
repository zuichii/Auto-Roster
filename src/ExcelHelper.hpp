#ifndef EXCEL_HELPER_H
#define EXCEL_HELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include "Employee.hpp"

class ExcelHelper{
    public:
    static std::vector<std::vector<std::string>> readExcel(std::string filePath);
    static void writeExcel(Employee emp, std::string filePath);
    static int generateId(std::string filePath);
    static void createCSV(std::map<int, std::vector<std::string>> roster);

};

std::vector<std::vector<std::string>> ExcelHelper::readExcel(std::string filePath){
    std::vector<std::vector<std::string>> data;

    std::ifstream file(filePath);
    if(!file.is_open()){
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return data;
    }

    std::string line; // skip header line
    std::getline(file, line);

    while(std::getline(file, line)){
        std::vector<std::string> row;
        size_t start = 0, end = 0;
        while((end = line.find(',', start)) != std::string::npos){
            row.push_back(line.substr(start, end-start));
            start = end+1;
        }
        row.push_back(line.substr(start));
        data.push_back(row);
    }
    file.close();
    return data;
};

void ExcelHelper::writeExcel(Employee emp, std::string filePath){
    std::ofstream file(filePath, std::ios::app);

    if(!file.is_open()){
        std::cerr << "Unable to open file: " << filePath << std::endl;
    }
    file << std::endl;
    file << emp.id << "," << emp.email << "," << emp.name << ","
     << (emp.morning ? "true" : "false") << ","
     << (emp.afternoon ? "true" : "false") << ","
     << (emp.evening ? "true" : "false") << ","
     << (emp.softgoods ? "true" : "false") << ","
     << (emp.hardgoods ? "true" : "false") << ","
     << (emp.checkouts ? "true" : "false") << ","
     << (emp.customer_service ? "true" : "false") << ","
     << (emp.nightfill ? "true" : "false");

    file.close();
}

int ExcelHelper::generateId(std::string filePath){
    std::ifstream file(filePath);
    if(!file.is_open()){
        std::cerr << "Unable to open file: " << filePath << std::endl; 
        return -1;
    }
    int id = 0;
    std::string line;
    std::getline(file, line); //skip header line
    
    while(std::getline(file, line)){
        
        std::istringstream iss(line);
        std::string token;
        std::getline(iss, token, ',');
        id = std::stoi(token);
    }
    file.close();
    return id+1;
}

void ExcelHelper::createCSV(std::map<int, std::vector<std::string>> roster){
    std::ofstream file("../src/roster.csv");
    if(!file.is_open()){
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }
    // Header row
    file << "Shift,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday" << std::endl;
    // Shifts
    std::vector<std::string> daysOfWeek = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for(auto day : daysOfWeek){
        file << "Morning,";
        for(auto& shift : roster){
            const std::vector<std::string> shifts = shift.second;
            if (!shifts.empty()) {
                file << shifts.front(); 
            }
            file << ",";
        }
        file << std::endl;
    }
    file.close();
}

#endif