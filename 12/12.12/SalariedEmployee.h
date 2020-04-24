// @file: SalariedEmployee.h

#ifndef SALARIED_H
#define SALARIED_H

#include "Employee.h"
#include <string>

class SalariedEmployee : public Employee {
  public:
    SalariedEmployee(const std::string&,
                     const std::string&,
                     const std::string&,
                     int,
                     int,
                     int,
                     double = 0.0);
    virtual ~SalariedEmployee() {}

    void setWeeklySalary(double);
    double getWeeklySalary() const;

    virtual double earnings() const override;
    virtual void print() const override;

  private:
    double weeklySalary;
};

#endif