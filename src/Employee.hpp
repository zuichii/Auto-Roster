#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>

class Employee{
    public:

    int id;
    std::string name, email;
    bool morning, afternoon, evening, softgoods, hardgoods, checkouts, customer_service, nightfill;

    Employee(int id, std::string name, std::string email, bool morning, bool afternoon, bool evening, bool softgoods, bool hardgoods, bool checkouts, bool customer_service, bool nightfill){
        this->id = id;
        this->name = name;
        this->email = email;
        this->morning = morning;
        this->afternoon = afternoon;
        this->evening = evening;
        this->softgoods = softgoods;
        this->hardgoods = hardgoods;
        this->checkouts = checkouts;
        this->customer_service = customer_service;
        this->nightfill = nightfill;
    } 
};
#endif