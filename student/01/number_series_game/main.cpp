#include <iostream>
#include <string>

using namespace std;

int main()
{
    int numbers = 6; // define parameter for input
    cout << "How many numbers would you like to have? ";
    cin >> numbers ; // input here

    // For-loop to print numbers from 1 - input number. Remember that range goes numbers - 1.
    // That's why you add numbers + 1.
    for (int num = 1; num < (numbers + 1); ++num) {

        // First evaluate whether the number is divisible by 3 AND 7 (no remainder)
        if ((num % 3 == 0) && (num % 7 == 0)) {
            cout << "zip boing" << endl;
        }

        // what to do if number is divisible by 3 (no remainder)
        else if (num % 3 == 0) {
            cout << "zip" << endl;
        }

        // what to do if number is divisible by 7 (no remainder)
        else if (num % 7 == 0) {
            cout << "boing" << endl;
        }

        // If number is just an ordinary number, print it as is
        else {
           cout << num << endl ;
        }
    }

    return EXIT_SUCCESS;
}
