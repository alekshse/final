#include "register.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Register::Register(const std::string &filename)
{
    LoadRecordsFromFile(filename);
    RebuildAllIndexes();
}
Register::Register()
{
}

Register::Register(const Register &other)
{
    for (Record *record : other.employees)
    {
        employees.push_back(new Record(*record));
    }
    RebuildAllIndexes();
}

Register::~Register()
{
    for (auto record : employees)
    {
        delete record;
    }
    employees.clear();
}

Register &Register::operator=(Register other)
{
    swap(*this, other);
    return *this;
}

void swap(Register &first, Register &second) noexcept
{
    using std::swap;
    swap(first.employees, second.employees);
    // Swap other members if needed, and then re-index if required
    first.RebuildAllIndexes(); // Make sure the indexes are correct after swapping
    second.RebuildAllIndexes();
}

void Register::LoadRecordsFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    std::string line;

    if (!file)
    {
        std::cerr << "Could not open the file: " << filename << std::endl;
        return;
    }

    while (getline(file, line))
    {
        Record *record = Record::CreateRecordFromCSV(line);
        if (record != nullptr)
        {
            employees.push_back(record);
        }
    }
}

std::ostream &operator<<(std::ostream &os, const Register &reg)
{
    for (const auto &employee : reg.employees)
    {
        if (employee != nullptr)
        {
            os << *employee << std::endl;
        }
    }
    return os;
}

const Register::EmplVector &Register::GetStorage() const
{
    return employees;
}

void Register::RebuildAllIndexes()
{
    nameIndex.clear();
    departmentIndex.clear();
    subordinateIndex.clear();
    dayIndex.clear();

    for (Record *record : employees)
    {
        if (record != nullptr)
        {
            nameIndex[record->GetEmployeeName()] = record;
            departmentIndex[record->GetDepartment()].push_back(record);
            subordinateIndex[record->GetBossName()].push_back(record);
            for (const std::string &day : record->GetWorkingDays())
            {
                dayIndex[day].push_back(record);
            }
        }
    }
}

const std::map<std::string, std::vector<Record *>> &Register::GetDepartmentIndex() const
{
    return departmentIndex;
}

Record *Register::FindRecordByName(const std::string &name) const
{
    auto it = nameIndex.find(name);
    if (it != nameIndex.end())
    {
        return it->second;
    }
    else
    {
        return nullptr;
    }
}

std::vector<Record *> Register::GetAllSubordinates(const std::string &bossName) const
{
    std::vector<Record *> allSubordinates;
    auto directSubordinates = subordinateIndex.find(bossName);

    if (directSubordinates != subordinateIndex.end())
    {
        for (Record *subordinate : directSubordinates->second)
        {
            allSubordinates.push_back(subordinate);
            // Recursively add indirect subordinates
            auto indirectSubordinates = GetAllSubordinates(subordinate->GetEmployeeName());
            allSubordinates.insert(allSubordinates.end(), indirectSubordinates.begin(), indirectSubordinates.end());
        }
    }

    return allSubordinates;
}

std::set<Record *> Register::GetEmployeesWorkingOnDays(const std::set<std::string> &days) const
{
    std::set<Record *> employeesWorkingOnDays;

    for (const std::string &day : days)
    {
        auto it = dayIndex.find(day);
        if (it != dayIndex.end())
        {
            for (Record *employee : it->second)
            {
                employeesWorkingOnDays.insert(employee);
            }
        }
    }

    return employeesWorkingOnDays;
}

void Register::Clear()
{
    DeallocateAndClear();
    RebuildAllIndexes();
}

void Register::DeallocateAndClear()
{
    for (Record *employee : employees)
    {
        delete employee;
    }
    employees.clear();
    nameIndex.clear();
    departmentIndex.clear();
    subordinateIndex.clear();
    dayIndex.clear();
}
