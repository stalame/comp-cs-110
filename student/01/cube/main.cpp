#include <iostream>

using namespace std;

int main()
{
    int num = 1;
    cout << "Enter a number: " ;
    cin >> num;

    int number_cubed = 1;
    number_cubed = num * num * num;

    // the cube of number num divided by square of num is num
    if (number_cubed / (num*num) == num) {
        cout << "The cube of " << num << " is " << number_cubed << "." << endl;
    }

    // If the above condition is false, then it's a case of overflow
    else {
        cout << "Error! The cube of " << num << " is not " << number_cubed << "." << endl;
    }

    return 0;
}
