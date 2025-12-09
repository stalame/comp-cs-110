#include "fraction.hh"
#include <iostream>

using namespace std;

int main()
{
    int num, den = 0;
    char slash;
    cout << "Enter a fraction (numerator/denominator): ";
    cin >> num;
    cin >> slash;
    cin >> den;
    if(den == 0) {
        cout << "Denominator cannot be zero" << endl;
        return EXIT_FAILURE;
    }
    Fraction f1(num, den);

    cout << "Enter another fraction (numerator/denominator): ";
    cin >> num;
    cin >> slash;
    cin >> den;
    if(den == 0) {
        cout << "Denominator cannot be zero" << endl;
        return EXIT_FAILURE;
    }
    Fraction f2(num, den);

    cout << "Sum: " << (f1+=f2) << endl;

    Fraction f4 = f1 * f2;
    cout << "Product: " << f4 << endl;

    if(f1 == f2) {
        cout << f1 << " and " << f2 << " are equal fractions" << endl;
    } else {
        cout << f1 << " and " << f2 << " are different fractions" << endl;
    }

    return EXIT_SUCCESS;
}
