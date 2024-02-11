#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <random>
#include <algorithm>
#include <curl/curl.h>
#include "Employee.hpp"
#include "ExcelHelper.hpp"

class Management{
    public:
    static void addEmployee();
    static std::vector<Employee> getEmployees();
    static std::map<int, std::vector<std::string>> generateRoster(std::vector<Employee> employees);
    static void sendEmails(std::set<std::string> recipients);
};

void Management::addEmployee(){
    int id = ExcelHelper::generateId("../tests/test_employees.csv");
    std::string name, email;
    bool morning, afternoon, evening, softgoods, hardgoods, checkouts, customer_service, nightfill;

    std::cout << "Enter employee name: " << std::endl;
    std::cin >> name;

    std::cout << "Enter employee email: " << std::endl;
    std::cin >> email;
    
    std::cout << "Enter employee morning availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> morning;
    std::cin.ignore(); 

    std::cout << "Enter employee afternoon availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> afternoon;
    std::cin.ignore(); 

    std::cout << "Enter employee evening availability, true or false: " << std::endl;
    std::cin >> std::boolalpha >> evening;
    std::cin.ignore(); 

    std::cout << "Enter employee softgoods preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> softgoods;
    std::cin.ignore(); 

    std::cout << "Enter employee hardgoods preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> hardgoods;
    std::cin.ignore(); 

    std::cout << "Enter employee checkouts preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> checkouts;
    std::cin.ignore(); 

    std::cout << "Enter employee customer service preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> customer_service;
    std::cin.ignore(); 

    std::cout << "Enter employee nightfill preference, true or false: " << std::endl;
    std::cin >> std::boolalpha >> nightfill;
    std::cin.ignore(); 

    Employee emp(id, name, email, morning, afternoon, evening, softgoods, hardgoods, checkouts, customer_service, nightfill);
    ExcelHelper::writeExcel(emp, "../tests/test_employees.csv");
}

std::vector<Employee> Management::getEmployees(){
    std::vector<std::vector<std::string>> data = ExcelHelper::readExcel("../src/employees.csv");
    std::vector<Employee> list;
    for(int i = 0; i < data.size(); i++){
        std::vector<std::string> row = data[i];

        int id = std::stoi(row[0]);
        std::string name = row[1];
        std::string email = row[2];
        bool morning = (row[3] == "true");
        bool afternoon = (row[4] == "true");
        bool evening = (row[5] == "true");
        bool softgoods = (row[6] == "true");
        bool hardgoods = (row[7] == "true");
        bool checkouts = (row[8] == "true");
        bool customerService = (row[9] == "true");
        bool nightfill = (row[10] == "true");

        Employee emp(id, name, email, morning, afternoon, evening, softgoods, hardgoods, checkouts, customerService, nightfill);
        list.push_back(emp);
    }
    return list;
}

std::map<int, std::vector<std::string>> Management::generateRoster(std::vector<Employee> employees) {
    std::map<int, std::vector<std::string>> weeklyRoster;
    const int numSoftgoodsShifts = 2;
    const int numHardgoodsShifts = 2;
    const int numCheckoutsShifts = 2;
    const int numCustomerServiceShifts = 1;
    const int numNightfillShifts = 1;

    for(int day = 0; day < 7; ++day){
        std::shuffle(employees.begin(), employees.end(), std::default_random_engine());
        std::vector<std::string> shifts;
        int softgoodsCounter = 0;
        int hardgoodsCounter = 0;
        int checkoutsCounter = 0;
        int customerServiceCounter = 0;
        int nightfillCounter = 0;

        for(auto employee : employees){
            // Morning and evening shifts
            if((employee.morning || employee.afternoon) &&
                (employee.softgoods || employee.hardgoods || employee.checkouts || employee.customer_service)){
                if(employee.softgoods && softgoodsCounter < numSoftgoodsShifts){
                    shifts.push_back("Morning shift (Softgoods)," + employee.name);
                    softgoodsCounter++;
                }else if(employee.hardgoods && hardgoodsCounter < numHardgoodsShifts){
                    shifts.push_back("Morning shift (Hardgoods)," + employee.name);
                    hardgoodsCounter++;
                }else if(employee.checkouts && checkoutsCounter < numCheckoutsShifts){
                    shifts.push_back("Morning shift (Checkouts)," + employee.name);
                    checkoutsCounter++;
                }else if(employee.customer_service && customerServiceCounter < numCustomerServiceShifts){
                    shifts.push_back("Morning shift (Customer Service)," + employee.name);
                    customerServiceCounter++;
                }
            }

            // Nightfill shifts
            if(employee.evening && employee.nightfill && nightfillCounter < numNightfillShifts){
                shifts.push_back("Evening shift (Nightfill)," + employee.name);
                nightfillCounter++;
            }

            // Check if all shifts are filled for the day
            if(softgoodsCounter == numSoftgoodsShifts && hardgoodsCounter == numHardgoodsShifts &&
                checkoutsCounter == numCheckoutsShifts && customerServiceCounter == numCustomerServiceShifts &&
                nightfillCounter == numNightfillShifts){
                break; 
            }
        }
        weeklyRoster[day] = shifts;
    }
    ExcelHelper::createCSV(weeklyRoster);
    return weeklyRoster;
}

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data){
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

void Management::sendEmails(std::set<std::string> emails){
    CURL* curl;
    CURLcode res;

    // Initialize curl
    curl = curl_easy_init();
    if(curl){
        // Set the SMTP server and port for Gmail
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:587");

        // Set sender email address
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, "example@gmail.com");

        // Add recipient email addresses
        struct curl_slist* recipients = NULL;
        for (auto email : emails) {
            recipients = curl_slist_append(recipients, email.c_str());
        }
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        // Set email subject
        curl_easy_setopt(curl, CURLOPT_READDATA, "Subject: Test email\n");

        // Set email body
        std::string email_body = "Test email";
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_READDATA, &email_body);

        // Attach file
        curl_mime* mime;
        curl_mimepart* part;
        mime = curl_mime_init(curl);
        part = curl_mime_addpart(mime);
        curl_mime_name(part, "attachment");
        curl_mime_filedata(part, "roster.csv");

        curl_easy_setopt(curl, CURLOPT_MIMEPOST, mime);

        // Set username and password for authentication
        curl_easy_setopt(curl, CURLOPT_USERNAME, "example@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "password");

        // Enable STARTTLS
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        // Send the email
        res = curl_easy_perform(curl);

        // Check for errors
        if(res != CURLE_OK) fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

#endif