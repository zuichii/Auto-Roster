#ifndef EXCEL_HELPER_H
#define EXCEL_HELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "Employee.hpp"

class ExcelHelper{
    public:
    static std::vector<std::vector<std::string>> readExcel(std::string filePath);
    static void writeExcel(Employee emp, std::string filePath);
    static int generateId(std::string filePath);
    static void createCSV(std::map<int, std::vector<std::string>> roster);
    static std::set<std::string> getEmails(std::string filepath);
    static void removeEmployeeByID(std::string filepath, int id);
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

void ExcelHelper::createCSV(std::map<int, std::vector<std::string>> roster) {
    std::ofstream file("../src/roster.csv");
    if(!file.is_open()){
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }
    // Header row
    file << "Day,Shift Type,Employee Email" << std::endl;
    

    std::map<int, std::string> dayName = {
        {0, "Monday"},
        {1, "Tuesday"},
        {2, "Wednesday"},
        {3, "Thursday"},
        {4, "Friday"},
        {5, "Saturday"},
        {6, "Sunday"}
    };
    
    int totalDays = roster.size();
    int currentDay = 1;

    // Shifts
    for(auto [day, shifts] : roster){
        for(auto shift : shifts){
            file << dayName[day] << "," << shift; 
            
            if(currentDay != totalDays || shift != shifts.back()) file << std::endl;
        }
        currentDay++;
    }
    file.close();
}

std::set<std::string> ExcelHelper::getEmails(std::string filepath){
    std::set<std::string> emails;

    std::ifstream file(filepath);
    if(!file.is_open()){
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return emails;
    }

    std::string line;
    std::getline(file, line); // skip header row

    while(std::getline(file, line)){
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ','); // skip day
        std::getline(ss, token, ','); // skip shift

        std::getline(ss, token, ',');
        emails.insert(token);
    }
    file.close();
    return emails;
}

void ExcelHelper::removeEmployeeByID(std::string filepath, int id){
    std::vector<std::string> lines;

    // Read the CSV file and store its contents in memory
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for reading." << std::endl;
        return;
    }
    std::string line;
    std::getline(file, line); // skip header row
    lines.push_back(line);
    while(std::getline(file, line)){
        // Split the line into fields
        std::stringstream ss(line);
        std::string field;
        std::getline(ss, field, ','); // Get id
        int employeeID = std::stoi(field);

        // If the ID does not match, store the line in memory
        if(employeeID != id){
            lines.push_back(line);
        }
    }
    file.close();

    // Write the updated data back to the CSV file
    std::ofstream outfile(filepath);
    if(!outfile.is_open()){
        std::cerr << "Error: Could not open file for writing." << std::endl;
        return;
    }
    for(auto line : lines){
        outfile << line;
        if(line != lines.back()) outfile << std::endl;        
    }
    outfile.close();
}

#endif