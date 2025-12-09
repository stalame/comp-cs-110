#include <iostream>
#include <string>

using namespace std;

int main()
{
    double temp = 25; // Room temperature is a great default :)
    cout << "Enter a temperature: ";
    cin >> temp;

    double c_to_f = (temp*1.8)+32; // calculation for celsius to fahrenheit
    double f_to_c = (temp-32)/1.8; // calculation for fahrenheit to celsius

    cout << temp << " degrees Celsius is " << c_to_f << " degrees Fahrenheit" << endl;
    cout << temp << " degrees Fahrenheit is " << f_to_c << " degrees Celsius" << endl;

    return EXIT_SUCCESS;
}
