#ifndef RECORD_HPP
#define RECORD_HPP

#include <string>
#include <vector>

class Record {
private:
    std::string employeeName;
    int employeeAge;
    std::string department;
    std::string position;
    std::string bossName;
    std::vector<std::string> workingDays;

public:
    // Constructor that takes a CSV string
    explicit Record(const std::string& csvString);

    // Create a Record from a CSV string
    static Record* CreateRecordFromCSV(const std::string& csvString);

    // Getters
    std::string GetEmployeeName() const;
    int GetEmployeeAge() const;
    std::string GetDepartment() const;
    std::string GetPosition() const;
    std::string GetBossName() const;
    std::vector<std::string> GetWorkingDays() const;
    // Friend operator<< to allow it to access private members  
    friend std::ostream& operator<<(std::ostream& os, const Record& record);
};

#endif // RECORD_HPP