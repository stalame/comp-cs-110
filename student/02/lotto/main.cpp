#include <iostream>
#include <string>

using namespace std;

bool positive_number(int number){
    // checks if an integer is positive
    if (number < 0){
        return false;
    }

    else{
        return true;
    }
}

unsigned long int factorial(unsigned long int number){
    // calculates the factorial of a number

    unsigned long int factorial = 1;
    for (unsigned int n = 1; n <= number; ++n){
        factorial *= n;
    }

    return factorial;
}

unsigned long int lotto_combinations(unsigned long int n, unsigned long int p){
    // calculates the combinations of in the Finnish lotto when there are n balls and p drawn balls

    unsigned long int n_factorial = 1;
    unsigned long int p_factorial = 1;
    unsigned long int n_p_factorial = 1;
    unsigned long int combinations = 1;

    n_factorial = factorial(n);
    p_factorial = factorial(p);
    n_p_factorial = factorial(n-p);

    combinations = n_factorial/(n_p_factorial*p_factorial);

    return combinations;
}

int main()
{
    // n = number of balls in the lottery
    // if default is 0, then it there will be a risk of division by zero
    unsigned long int n = 1;
    cout << "Enter the total number of lottery balls: ";
    cin >> n;

    // p = number of drawn balls
    // if default is 0, then there is the risk for division by zero
    unsigned long int p = 1;
    cout << "Enter the number of drawn balls: ";
    cin >> p;

    // check the positivity of the input numbers n and p.
    if (not positive_number(n) or not positive_number(p)){
        cout << "The number of balls must be a positive number." << endl;
        return EXIT_FAILURE;
    }

    // p cannot be greater than n
    if (p > n){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return EXIT_FAILURE;
    }

    unsigned long int combinations = 1;
    combinations = lotto_combinations(n, p);

    cout << "The probability of guessing all " << p << " balls correctly is " << 1 << "/" << combinations << endl;

    return EXIT_SUCCESS;
}
