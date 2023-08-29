#include "book.hh"
#include <iostream>

Book::Book(std::string author, std::string name):
    author_(author), name_(name){

}

void Book::print() const{
    std::cout << author_ << " : " << name_ << std::endl;

    // print more details
    if (Book::is_loaned_ == false) {
        // book not loaned, print available
        std::cout << "- available" << std::endl;
    } else {
        // book is loaned, print loan info
        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout <<"- to be returned: ";
        return_date_.print();

    }

}

void Book::renew() {
    if (is_loaned_ == false) {
        // not loaned, cannot renew
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    } else {
        // is loaned, try to renew
        return_date_.advance(28);
    }
}

void Book::loan(Date date) {
    if (is_loaned_ == false) {
        // not loaned, set loan date and loan book
        loan_date_ = date;
        date.advance(28);

        // set return date
        return_date_ = date;
        is_loaned_ = true;
    } else {
        // already loaned
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::give_back() {
    // give back book
    is_loaned_ = false;
}
