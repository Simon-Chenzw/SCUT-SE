/**
 *  @brief:code of 12.12
 *  @author:Simon_Chen
 */

#include "CommissionEmployee.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CommissionEmployee::CommissionEmployee(const string& first,
                                       const string& last,
                                       const string& ssn,
                                       int month,
                                       int day,
                                       int year,
                                       double sales,
                                       double rate):
      Employee(first, last, ssn, month, day, year) {
    setGrossSales(sales);
    setCommissionRate(rate);
}

void CommissionEmployee::setGrossSales(double sales) {
    if (sales >= 0.0)
        grossSales = sales;
    else
        throw invalid_argument("Gross sales must bu >=0.0");
}

double CommissionEmployee::getGrossSales() const {
    return grossSales;
}

void CommissionEmployee::setCommissionRate(double rate) {
    if (rate > 0.0 && rate < 1.0)
        commissionRate = rate;
    else
        throw invalid_argument("Commission rate must be > 0.0 and < 1.0");
}

double CommissionEmployee::getCommissionRate() const {
    return commissionRate;
}

double CommissionEmployee::earnings() const {
    return getCommissionRate() * getGrossSales();
}

void CommissionEmployee::print() const {
    cout << "commission employee: ";
    Employee::print();
    cout << "\ngross sales: " << getGrossSales() << "; commission rate: " << getCommissionRate();
}
