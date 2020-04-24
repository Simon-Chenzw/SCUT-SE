// @problem:12.14

#include <bits/stdc++.h>
using namespace std;

class Account {
  public:
    Account(double);
    virtual void credit(double);
    virtual bool debit(double);
    virtual double calculateInterest() const;
    double getBalance() const;

  private:
    double Balance;
};

class SavingsAccount : public Account {
  public:
    SavingsAccount(double, double);
    virtual double calculateInterest() const override;

  private:
    double InterestRate;
};

class CheckingAccount : public Account {
  public:
    CheckingAccount(double, double);
    virtual void credit(double) override;
    virtual bool debit(double) override;

  private:
    double CostPerDeal;
};

Account::Account(double _Balance) : Balance(_Balance) {
    if (Balance < 0) {
        Balance = 0;
        cerr << "balance can't be negative";
    }
}

void Account::credit(double value) { Balance += value; }

bool Account::debit(double value) {
    if (value <= Balance) {
        Balance -= value;
        return true;
    }
    else {
        cerr << "Debit amount exceeded account balance";
        return false;
    }
}

double Account::calculateInterest() const { return 0; }

double Account::getBalance() const { return Balance; }

SavingsAccount::SavingsAccount(double _Balance, double _InterestRate)
      : Account(_Balance), InterestRate(_InterestRate) {}

double SavingsAccount::calculateInterest() const { return getBalance() * InterestRate; }

CheckingAccount::CheckingAccount(double _Balance, double _CostPerDeal)
      : Account(_Balance), CostPerDeal(_CostPerDeal) {}

void CheckingAccount::credit(double value) {
    if (value >= CostPerDeal)
        Account::credit(value - CostPerDeal);
    else
        Account::debit(CostPerDeal - value);
}

bool CheckingAccount::debit(double value) {
    if (!Account::debit(value + CostPerDeal)) cerr << "Debit amount exceeded account balance";
}

int main() {
    SavingsAccount test1(120, 0.1);
    CheckingAccount test2(1000, 9);
    vector<Account*> accounts = {&test1, &test2};
    cout << "Initial Balance\n";
    for (auto& Ptr : accounts) {
        cout << Ptr->getBalance() << '\n';
    }
    cout << "\ndebit $10\n";
    for (auto& Ptr : accounts) {
        Ptr->debit(10);
        if (typeid(*Ptr) == typeid(SavingsAccount)) Ptr->credit(Ptr->calculateInterest());
        cout << Ptr->getBalance() << '\n';
    }
    cout << "\ncredit $30\n";
    for (auto& Ptr : accounts) {
        Ptr->debit(30);
        if (typeid(*Ptr) == typeid(SavingsAccount)) Ptr->credit(Ptr->calculateInterest());
        cout << Ptr->getBalance() << '\n';
    }
}