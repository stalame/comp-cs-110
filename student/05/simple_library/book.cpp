#include "book.hh"
#include "date.hh"
#include <string>
#include <iostream>

// functions to implement:
// PRIVATE functions:
//      bool isAvailable();
// PUBLIC functions:
//      void renew();
//      void give_back();
//      void print();
//      void loan();


using namespace std;

Book::Book(const string& author, const string& title):
    author_(author), title_(title){
}

void Book::print(){
    cout << author_ << " : " << title_ << endl;

    if (is_available_){
        cout << "- available" << endl;
    }

    else{
        cout << "- loaned: ";
        loan_date_.print();
        cout << "- to be returned: ";
        return_date_.print();
    }
}

void Book::loan(Date& loan_date)
{
    if (!is_available_){
        cout << "Already loaned: cannot be loaned" << endl;
        return;
    }

    loan_date_ = loan_date;
    loan_date.advance(28);
    return_date_ = loan_date;
    is_available_ = false;
}

void Book::renew(){

    if (is_available_){ // you cannot renew a loan that doesn't exist
        cout << "Not loaned: cannot be renewed" << endl;
        return;
    }

    return_date_.advance(28);
}

void Book::give_back(){
    loan_date_.~Date();
    return_date_.~Date();
    is_available_ = true;
}
