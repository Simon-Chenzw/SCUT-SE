// @file: BasePlusCommissionEmployee.h

#ifndef BASEPLUS_H
#define BASEPLUS_H

#include "CommissionEmployee.h"
#include <string>
using namespace std;

class BasePlusCommissionEmployee : public CommissionEmployee {
  public:
    BasePlusCommissionEmployee(const string&,
                               const string&,
                               const string&,
                               int,
                               int,
                               int,
                               double = 0.0,
                               double = 0.0,
                               double = 0.0);

    void setBaseSalary(double);
    double getBaseSalary() const;

    virtual double earnings() const override;
    virtual void print() const override;

  private:
    double baseSalary;
};

#endif