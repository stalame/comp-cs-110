#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    int pos_num = 1;
    cout << "Enter a positive number: ";
    cin >> pos_num;

    // Error line for incorrect input
    if (pos_num < 1) {
        cout << "Only positive numbers accepted" << endl;
        return EXIT_SUCCESS;
    }

    // initial factors, start easy lol
    int factor_1 = 1;
    int factor_2 = pos_num;

    // values to check against
    int closest_1 = factor_1;
    int closest_2 = factor_2;

    for (; factor_1 < pos_num; ++factor_1) {
        // check if it's divisible by factor_1
        if (pos_num % factor_1 == 0) {
            // update factor_2 and all other parameters if above condition is true
            factor_2 = pos_num/factor_1;

            if (abs(closest_1 - closest_2) > abs(factor_1 - factor_2)) {
                closest_1 = factor_1;
                closest_2 = factor_2;
            }

            if (closest_1 == closest_2) {
                break;
            }
        }
    }

    cout << closest_1 * closest_2 << " = " << closest_1 << " * " << closest_2 << endl;

    return EXIT_SUCCESS;
}
