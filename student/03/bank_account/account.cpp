#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
 owner_(owner), has_credit_(has_credit){

    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}

// print account info Tupu : FI00 1234 01 : 100 euros
void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << money_<< " euros" << std::endl;
}

void Account::set_credit_limit(int credit_amount) {
    // set credit limit if enabled
    if (has_credit_ == true) {
        credit_limit_ = credit_amount;
    } else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }

}

void Account::save_money(int money_amount){
    // add money amount to account
    money_ += money_amount;
}

bool Account::take_money(int money_amount) {
    // check if money can be taken
    int new_bal = money_ - money_amount;
    // check if we can proceed with taking money, take into account credit limit
    if ((credit_limit_ + new_bal) < 0) {

        // balance under 0, display error
        if (has_credit_ == false) {
            // display normal error
            std::cout << "Cannot take money: balance underflow" << std::endl;
        } else {
            // has credit card, display credit error
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }

        // failed, return false
        return false;
    } else {
        // not under 0 euros, money can be taken
        //take money from account
        money_ = new_bal;
        std::cout << money_amount << " euros taken: new balance of " << iban_ << " is "<< money_ << " euros" << std::endl;

        // return success
        return true;
    }


}

void Account::transfer_to(Account& destination, int money_amount) {
    // try to transfer money
    if (Account::take_money(money_amount) == false) {
        // notify of failed transfer
        std::cout << "Transfer from " << Account::iban_ << " failed" << std::endl;
    } else {
        // success, move money to destination account
        destination.save_money(money_amount);
    }

}
