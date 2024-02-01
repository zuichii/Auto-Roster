#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

class Employee{
    int id;
    bool avail_morning;
    bool avail_afternoon;
    bool avail_evening;
    std::vector<std::string> role_pref;

    Employee(int id, bool morning, bool afternoon, bool evening, std::vector<std::string> roles){
        this->id = id;
        this->avail_morning = morning;
        this->avail_afternoon = afternoon;
        this->avail_evening = evening;
        this->role_pref = roles;
    } 
};
#endif