#include "account.hh"
#include <iostream>
#include <cmath>

using namespace std;

Account::Account(const string& owner, bool has_credit):
owner_(owner), has_credit_(has_credit)
{
    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        cout << "Too many accounts" << endl;
    }
    suffix.append(to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

void Account::transfer_to(Account& account, int amount){
    take_money(amount);
    if (!transfer_successful_){
        cout << "Transfer from " << iban_ << " failed" << endl;
        return;
    }

    account.save_money(amount);
}

void Account::save_money(int amount){
    balance_ += amount;
}

void Account::set_credit_limit(int limit){
    if (!has_credit_){
        cout << "Cannot set credit limit: the account has no credit card" << endl;
        return;
    }

    credit_limit_ = limit;
}

void Account::take_money(int amount){
    if (amount > balance_ && !has_credit_){
        cout << "Cannot take money: balance underflow" << endl;
        transfer_successful_ = false;
        return;
    }

    else if (amount > balance_ && has_credit_){
        int new_balance = balance_ - amount;

        if(new_balance < 0 && abs(new_balance) > credit_limit_){
            cout << "Cannot take money: credit limit overflow" << endl;
            transfer_successful_ = false;
            return;
        }

        balance_ = new_balance;
    }

    else{
        balance_ -= amount;
    }

    transfer_successful_ = true;
    cout << amount << " euros taken: new balance of " << iban_;
    cout << " is " << balance_ << " euros" << endl;
}

void Account::print(){
    cout << owner_ << " : " << iban_ << " : " << balance_ << " euros" << endl;
}
