#ifndef EXCEL_HELPER_H
#define EXCEL_HELPER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class ExcelHelper{
    public:
    static std::vector<std::vector<std::string>> readExcel(std::string filePath);

};

std::vector<std::vector<std::string>> ExcelHelper::readExcel(std::string filePath){
    std::vector<std::vector<std::string>> data;

    std::ifstream file(filePath);
    if(!file.is_open()){
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return data;
    }

    std::string line; // skip the first line of headings
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

#endif