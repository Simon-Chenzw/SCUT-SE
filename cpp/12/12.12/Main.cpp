/**
 *  @brief:code of 12.12
 *  @author:Simon_Chen
 */

#include <iomanip>
#include <iostream>
#include <vector>
#include "BasePlusCommissionEmployee.h"
#include "CommissionEmployee.h"
#include "Employee.h"
#include "SalariedEmployee.h"
using namespace std;

void virtualViaPointer(const Employee* const baseClassPtr) {
    baseClassPtr->print();
    cout << "\nearned $" << baseClassPtr->earnings() << "\n\n";
}

void virtualViaReference(const Employee& baseClassRef) {
    baseClassRef.print();
    cout << "\nearned $" << baseClassRef.earnings() << "\n\n";
}

int main() {
    cout << fixed << setprecision(2);
    SalariedEmployee salariedEmployee("John", "Smith", "111-11-1111", 5, 21, 1982, 800);
    CommissionEmployee commissionEmployee("Sue", "Jones", "333-33-3333", 6, 30, 1976, 10000, 0.06);
    BasePlusCommissionEmployee basePlusCommissionEmployee("Bob", "Lewis", "444-44-4444", 7, 12, 1984, 5000, 0.04, 300);

    cout << "Employees processed polymorphically via dynamic binding:\n\n";
    salariedEmployee.print();
    cout << "\nearned $" << salariedEmployee.earnings() << "\n\n";
    commissionEmployee.print();
    cout << "\nearned $" << commissionEmployee.earnings() << "\n\n";
    basePlusCommissionEmployee.print();
    cout << "\nearned $" << basePlusCommissionEmployee.earnings() << "\n\n";

    vector<Employee*> employees = {&salariedEmployee, &commissionEmployee, &basePlusCommissionEmployee};
    cout << "Employees processed polymorphically via dynamic binding:\n\n";

    cout << "Virtual function calls made off base-class pointers:\n\n";
    for (auto employeePtr : employees) virtualViaPointer(employeePtr);

    cout << "Virtual function calls made off base-class references\n\n";
    for (auto employeePtr : employees) virtualViaReference(*employeePtr);

    // Birthday's Bonus
    cout << "additional birthday bonus earnings\n\n";
    int thisMonth;
    cout << "Enter the number of this month:";
    cin >> thisMonth;
    cout << "\n";
    for (auto employeePtr : employees) {
        if (employeePtr->getBirthDate().getMonth() == thisMonth) {
            employeePtr->print();
            cout << "\nbirth in this month, additional $100";
            cout << "\nearned $" << employeePtr->earnings() + 100 << "\n\n";
        }
        else {
            employeePtr->print();
            cout << "\nearned $" << employeePtr->earnings() << "\n\n";
        }
    }
}