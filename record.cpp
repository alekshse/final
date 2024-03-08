#include "record.hpp"
#include <sstream>
#include <iterator>
#include <iomanip> // For std::setw and std::left


std::vector<std::string> SplitString(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

Record::Record(const std::string& csvString) {
    auto tokens = SplitString(csvString, '\t'); // Assuming '\t' is used as a delimiter in the actual CSV
    employeeName = tokens[0];
    employeeAge = std::stoi(tokens[1]);
    department = tokens[2];
    position = tokens[3];
    bossName = tokens[4];
    for (size_t i = 5; i < tokens.size(); ++i) {
        workingDays.push_back(tokens[i]);
    }
}

Record* Record::CreateRecordFromCSV(const std::string& csvString) {
    return new Record(csvString);
}

std::string Record::GetEmployeeName() const {
    return employeeName;
}

int Record::GetEmployeeAge() const {
    return employeeAge;
}

std::string Record::GetDepartment() const {
    return department;
}

std::string Record::GetPosition() const {
    return position;
}

std::string Record::GetBossName() const {
    return bossName;
}

std::vector<std::string> Record::GetWorkingDays() const {
    return workingDays;
}

std::ostream& operator<<(std::ostream& os, const Record& record) {
    int nameWidth = 20;
    int ageWidth = 5;
    int deptWidth = 15;
    int posWidth = 15;
    int bossWidth = 20;
    int daysWidth = 30;

    os << std::left << std::setw(nameWidth) << record.GetEmployeeName()
       << std::setw(ageWidth) << record.GetEmployeeAge()
       << std::setw(deptWidth) << record.GetDepartment()
       << std::setw(posWidth) << record.GetPosition()
       << std::setw(bossWidth) << record.GetBossName();

    std::string workingDaysStr;
    for (const auto& day : record.GetWorkingDays()) {
        workingDaysStr += day + " ";
    }
    os << std::setw(daysWidth) << workingDaysStr;

    return os;
}