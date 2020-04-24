// @file: BasePlusCommissionEmployee.cpp

#include "BasePlusCommissionEmployee.h"
#include <iostream>
#include <stdexcept>
using namespace std;

BasePlusCommissionEmployee::BasePlusCommissionEmployee(const string& first,
                                                       const string& last,
                                                       const string& ssn,
                                                       int month,
                                                       int day,
                                                       int year,
                                                       double sales,
                                                       double rate,
                                                       double salary)
      : CommissionEmployee(first, last, ssn, month, day, year, sales, rate) {
    setBaseSalary(salary);
}

void BasePlusCommissionEmployee::setBaseSalary(double salary) {
    if (salary >= 0.0)
        baseSalary = salary;
    else
        throw invalid_argument("Salary must be >= 0.0");
}

double BasePlusCommissionEmployee::getBaseSalary() const { return baseSalary; }

double BasePlusCommissionEmployee::earnings() const {
    return getBaseSalary() + CommissionEmployee::earnings();
}

void BasePlusCommissionEmployee::print() const {
    cout << "base-salaried ";
    CommissionEmployee::print();
    cout << "; base salary: " << getBaseSalary();
}