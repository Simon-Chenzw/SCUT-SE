// @problem:11.10

#include <bits/stdc++.h>

class Account {
  public:
    Account(double);
    void credit(double);
    bool debit(double);
    double getBalance() const;

  private:
    double Balance;
};

class SavingsAccount : public Account {
  public:
    SavingsAccount(double, double);
    double calculateInterest() const;

  private:
    double InterestRate;
};

class CheckingAccount : public Account {
  public:
    CheckingAccount(double, double);
    void credit(double);
    bool debit(double);

  private:
    double CostPerDeal;
};

Account::Account(double _Balance) : Balance(_Balance) {
    if (Balance < 0) {
        Balance = 0;
        std::cerr << "balance can't be negative";
    }
}

void Account::credit(double value) { Balance += value; }

bool Account::debit(double value) {
    if (value <= Balance) {
        Balance -= value;
        return true;
    }
    else {
        std::cerr << "Debit amount exceeded account balance";
        return false;
    }
}

double Account::getBalance() const { return Balance; }

SavingsAccount::SavingsAccount(double _Balance, double _InterestRate) :
      Account(_Balance),
      InterestRate(_InterestRate) {}

double SavingsAccount::calculateInterest() const { return getBalance() * InterestRate; }

CheckingAccount::CheckingAccount(double _Balance, double _CostPerDeal) :
      Account(_Balance),
      CostPerDeal(_CostPerDeal) {}

void CheckingAccount::credit(double value) {
    if (value >= CostPerDeal)
        Account::credit(value - CostPerDeal);
    else
        Account::debit(CostPerDeal - value);
}

bool CheckingAccount::debit(double value) {
    if (!Account::debit(value + CostPerDeal)) std::cerr << "Debit amount exceeded account balance";
}