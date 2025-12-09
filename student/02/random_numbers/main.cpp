#include <iostream>
#include <random>
#include <string>

using namespace std;

void produce_random_numbers(unsigned int lower, unsigned int upper)
{
    // Implement your function here
    // random number generator that continues generating numbers with input seed as long as
    // user types anything but q, which terminates the program.

    int seed = 1;

    cout << "Enter a seed value: ";
    cin >> seed;

    // create random number generator with given seed
    default_random_engine gen(seed);

    uniform_int_distribution<int> distr(lower, upper);

    while (true){
        // generate a loop that prints random numbers until user types q
        string key = "";

        cout << "\n";
        cout << "Your drawn random number is " << distr(gen) << endl;
        cout << "Press q to quit or any other key to continue: ";
        cin >> key;

        if (key == "q"){
            break;
        }
    }

}

int main()
{
    unsigned int lower_bound, upper_bound;
    cout << "Enter a lower bound: ";
    cin >> lower_bound;
    cout << "Enter an upper bound: ";
    cin >> upper_bound;

    if(lower_bound >= upper_bound)
    {
        cout << "The upper bound must be strictly greater than the lower bound"
             << endl;
        return EXIT_FAILURE;
    }

    produce_random_numbers(lower_bound, upper_bound);

    return EXIT_SUCCESS;
}
