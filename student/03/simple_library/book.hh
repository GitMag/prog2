#ifndef BOOK_HH
#define BOOK_HH

#include <iostream>
#include <date.hh>

class Book
{
public:   
    //init functions in constructor
    Book(std::string autohor, std::string name);

    void print() const;
    void loan(Date date);
    void renew();
    void give_back();

private:

    // define private vars
    std::string author_;
    std::string name_;

    bool is_loaned_ = false;
    Date loan_date_;
    Date return_date_;
};

#endif // BOOK_HH
