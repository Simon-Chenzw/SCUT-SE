// @file: Employee.cpp

#include "Employee.h"
#include <iostream>
using namespace std;

Employee::Employee(const string& first,
                   const string& last,
                   const string& ssn,
                   int month,
                   int day,
                   int year)
      : firstName(first), lastName(last), socialSecurityNumber(ssn), birthDate(month, day, year) {}

void Employee::setFirstName(const string& first) { firstName = first; }

string Employee::getFirstName() const { return firstName; }

void Employee::setLastName(const string& last) { lastName = last; }

string Employee::getLastName() const { return lastName; }

void Employee::setSocialSecurityNumber(const string& ssn) { socialSecurityNumber = ssn; }

string Employee::getSocialSecurityNumber() const { return socialSecurityNumber; }

Date Employee::getBirthDate() const { return birthDate; }

void Employee::print() const {
    cout << getFirstName() << ' ' << getLastName()
         << "\nsocial security number: " << getSocialSecurityNumber();
}