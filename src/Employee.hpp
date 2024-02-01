#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

class Employee{
    public:

    int id;
    bool availMorning;
    bool availAfternoon;
    bool availEvening;
    std::vector<std::string> rolePref;

    Employee(int id, bool morning, bool afternoon, bool evening, std::vector<std::string> roles){
        this->id = id;
        this->availMorning = morning;
        this->availAfternoon = afternoon;
        this->availEvening = evening;
        this->rolePref = roles;
    } 
};
#endif