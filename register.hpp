#ifndef REGISTER_HPP
#define REGISTER_HPP

#include "record.hpp"
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>

class Register {
private:
    typedef std::vector<Record*> EmplVector;
    EmplVector employees;
    std::map<std::string, Record*> nameIndex;
    std::map<std::string, std::vector<Record*>> departmentIndex; 
    std::map<std::string, std::vector<Record*>> subordinateIndex; 
    std::map<std::string, std::vector<Record*>> dayIndex;

    void DeallocateAndClear();
    

public:
    // Clean constructor
    Register();
    // Constructor with load
    Register(const std::string& filename);
    // Copy constructor
    Register(const Register& other);
    ~Register();

    // Copy assignment operator
    Register& operator=(Register other); // Note: 'other' passed by value for copy-and-swap

    // Load CSV file
    void LoadRecordsFromFile(const std::string& filename);
    // Additional methods for processing and accessing records could be declared here
    const EmplVector& GetStorage() const;


    // Lookup record by name
    Record* FindRecordByName(const std::string& name) const;

    // Get the department index
    const std::map<std::string, std::vector<Record*>>& GetDepartmentIndex() const;

    // Rebuild all indexes
    void RebuildAllIndexes();

    // Get all subordinates (direct and indirect) of a given employee
    std::vector<Record*> GetAllSubordinates(const std::string& bossName) const;

    // Get employees working on given days
    std::set<Record*> GetEmployeesWorkingOnDays(const std::set<std::string>& days) const;

    // Clearing all records and indexes
    void Clear();

    // Friend operator<< to allow it to access private members
    friend std::ostream& operator<<(std::ostream& os, const Register& reg);

    // Swap method
    friend void swap(Register& first, Register& second) noexcept; // noexcept swap function


};

#endif // REGISTER_HPP