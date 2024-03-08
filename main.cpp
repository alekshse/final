#include "register.hpp"
#include <iostream>
#include <string>
#include <set>
#include <limits> 
#include <sstream>
#include <csignal>


void printMenu()
{
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "Employee database\n=================\n"
              << "(L) Load a file\n"
              << "(C) Clear a dataset\n"
              << "(N) Print number of records in a dataset\n"
              << "(P) Print all records\n"
              << "(E) Print an employee by their name\n"
              << "(A) Print all employees with an age in a given range\n"
              << "(D) Print employees distributed by departments\n"
              << "(S) Print all subordinates of a given employee\n"
              << "(W) Print employees working on given days\n"
              << "(X) Exit\n"
              << "Choose an action: ";
}

void printRecords(const std::vector<Record *> &records)
{
    for (const auto &record : records)
    {
        std::cout << *record << std::endl;
    }
}

void printEmployeesByDepartment(const std::map<std::string, std::vector<Record *>> &departmentIndex)
{
    for (const auto &entry : departmentIndex)
    {
        std::cout << "Department: " << entry.first << std::endl;
        printRecords(entry.second);
    }
}

std::set<std::string> splitStringToSet(const std::string &input)
{
    std::istringstream iss(input);
    std::set<std::string> resultSet;
    std::string token;

    while (iss >> token)
    {
        resultSet.insert(token);
    }

    return resultSet;
}

int main()
{
    // Ignore SIGWINCH, without this? resize creates strange sideeffects on macOS
    std::signal(SIGWINCH, SIG_IGN);
    Register reg;
    char choice;

    do
    {
        printMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        std::cout << "=================\n";

        if (reg.GetStorage().empty() && choice != 'L' && choice != 'C' && choice != 'X')
        {
            std::cout << "Register is empty, please load a file." << std::endl;
            std::cout << "=================\n";
            continue;
        }

        switch (choice)
        {
        case 'L':
        {
            std::string filename;
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            reg.LoadRecordsFromFile(filename);
            reg.RebuildAllIndexes();
            break;
        }
        case 'C':
            reg.Clear();
            break;
        case 'N':
            std::cout << "Number of records: " << reg.GetStorage().size() << std::endl;
            break;
        case 'P':
            printRecords(reg.GetStorage());
            break;
        case 'E':
        {
            std::string name;
            std::cout << "Enter employee name: ";
            std::getline(std::cin, name);
            Record *record = reg.FindRecordByName(name);
            if (record)
            {
                std::cout << *record << std::endl;
            }
            else
            {
                std::cout << "Employee not found." << std::endl;
            }
            break;
        }
        case 'A':
        {
            int minAge, maxAge;
            std::cout << "Enter minimum age: ";
            std::cin >> minAge;
            std::cout << "Enter maximum age: ";
            std::cin >> maxAge;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer after reading numbers

            const auto &records = reg.GetStorage();
            std::vector<Record *> employeesInAgeRange;

            for (Record *employee : records)
            {
                if (employee->GetEmployeeAge() >= minAge && employee->GetEmployeeAge() <= maxAge)
                {
                    employeesInAgeRange.push_back(employee);
                }
            }

            if (!employeesInAgeRange.empty())
            {
                std::cout << "Employees in age range " << minAge << " to " << maxAge << ":" << std::endl;
                for (Record *employee : employeesInAgeRange)
                {
                    std::cout << *employee << std::endl;
                }
            }
            else
            {
                std::cout << "No employees found in the specified age range." << std::endl;
            }
            break;
        }
        case 'D':
            printEmployeesByDepartment(reg.GetDepartmentIndex());
            break;
        case 'S':
        {
            std::string bossName;
            std::cout << "Enter boss name: ";
            std::getline(std::cin, bossName);
            auto subordinates = reg.GetAllSubordinates(bossName);
            printRecords(subordinates);
            break;
        }
        case 'W':
        {
            std::string inputDays;
            std::cout << "Enter days separated by space (e.g., Mon Tue Wed): ";
            std::getline(std::cin, inputDays);

            std::set<std::string> days = splitStringToSet(inputDays);

            auto employees = reg.GetEmployeesWorkingOnDays(days);

            if (!employees.empty())
            {
                std::cout << "Employees working on the given days:" << std::endl;
                for (Record *employee : employees)
                {
                    std::cout << *employee << std::endl;
                }
            }
            else
            {
                std::cout << "No employees work on the given days." << std::endl;
            }
            break;
        }
        case 'X':
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        std::cout << "=================\n";
    } while (choice != 'X');

    return 0;
}
