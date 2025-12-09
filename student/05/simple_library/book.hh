#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"

using namespace std;

class Book
{
public:
    Book(const string& author, const string& title);
    void renew();
    void give_back();
    void print();
    void loan(Date& loan_date);

private:
    string author_;
    string title_;
    Date loan_date_;
    Date return_date_;
    bool is_available_ = true;
};

#endif // BOOK_HH
