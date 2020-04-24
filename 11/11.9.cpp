// @problem:11.9

#include <bits/stdc++.h>
using namespace std;
class Package {
  public:
    Package(string, string, string, string, string, string, string, string, int, double, double);
    double calculateCost() const;

  protected:
    string ConsignorName;  // send
    string ConsignorAddress;
    string ConsignorCity;
    string ConsignorState;
    string ConsigneeName;  // get
    string ConsigneeAddress;
    string ConsigneeCity;
    string ConsigneeState;
    int PostCode;
    double Weight;
    double CostPerWeight;
};

class TwoDayPackage : public Package {
  public:
    TwoDayPackage(string,
                  string,
                  string,
                  string,
                  string,
                  string,
                  string,
                  string,
                  int,
                  double,
                  double,
                  double);
    double calculateCost() const;

  private:
    double ExtraCost;
};

class OvernightPackage : public Package {
  public:
    OvernightPackage(string,
                     string,
                     string,
                     string,
                     string,
                     string,
                     string,
                     string,
                     int,
                     double,
                     double,
                     double);
    double calculateCost() const;

  private:
    double ExtraCostPerWeight;
};

Package::Package(string _ConsignorName,
                 string _ConsignorAddress,
                 string _ConsignorCity,
                 string _ConsignorState,
                 string _ConsigneeName,
                 string _ConsigneeAddress,
                 string _ConsigneeCity,
                 string _ConsigneeState,
                 int _PostCode,
                 double _Weight,
                 double _CostPerWeight)
      : ConsignorName(_ConsignorName),
        ConsignorAddress(_ConsignorAddress),
        ConsignorCity(_ConsignorCity),
        ConsignorState(_ConsignorState),
        ConsigneeName(_ConsigneeName),
        ConsigneeAddress(_ConsigneeAddress),
        ConsigneeCity(_ConsigneeCity),
        ConsigneeState(_ConsigneeState),
        PostCode(_PostCode),
        Weight(_Weight),
        CostPerWeight(_CostPerWeight) {
    if (Weight <= 0) throw invalid_argument("weight isn't positive");
    if (CostPerWeight <= 0) throw invalid_argument("CostPerWeight isn't positive");
}

double Package::calculateCost() const { return Weight * CostPerWeight; }

TwoDayPackage::TwoDayPackage(string _ConsignorName,
                             string _ConsignorAddress,
                             string _ConsignorCity,
                             string _ConsignorState,
                             string _ConsigneeName,
                             string _ConsigneeAddress,
                             string _ConsigneeCity,
                             string _ConsigneeState,
                             int _PostCode,
                             double _Weight,
                             double _CostPerWeight,
                             double _ExtraCost)
      : Package(_ConsignorName,
                _ConsignorAddress,
                _ConsignorCity,
                _ConsignorState,
                _ConsigneeName,
                _ConsigneeAddress,
                _ConsigneeCity,
                _ConsigneeState,
                _PostCode,
                _Weight,
                _CostPerWeight),
        ExtraCost(_ExtraCost) {}

double TwoDayPackage::calculateCost() const { return Weight * CostPerWeight + ExtraCost; }

OvernightPackage::OvernightPackage(string _ConsignorName,
                                   string _ConsignorAddress,
                                   string _ConsignorCity,
                                   string _ConsignorState,
                                   string _ConsigneeName,
                                   string _ConsigneeAddress,
                                   string _ConsigneeCity,
                                   string _ConsigneeState,
                                   int _PostCode,
                                   double _Weight,
                                   double _CostPerWeight,
                                   double _ExtraCostPerWeight)
      : Package(_ConsignorName,
                _ConsignorAddress,
                _ConsignorCity,
                _ConsignorState,
                _ConsigneeName,
                _ConsigneeAddress,
                _ConsigneeCity,
                _ConsigneeState,
                _PostCode,
                _Weight,
                _CostPerWeight),
        ExtraCostPerWeight(_ExtraCostPerWeight) {}

double OvernightPackage::calculateCost() const {
    return Weight * (CostPerWeight + ExtraCostPerWeight);
}