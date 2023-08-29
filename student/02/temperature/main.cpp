#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // read temp
    double temp;
    cin >> temp;

    // convert celcius to fahrenheit
    double temp_cf = temp * 1.8 + 32;

    // convert fahrenheit to celcius
    double temp_fc = (temp - 32) / 1.8;

    // print temp from c to f
    cout << temp << " degrees Celsius is " << temp_cf << " degrees Fahrenheit" << endl;
    // print temp from f to c
    cout << temp << " degrees Fahrenheit is " << temp_fc << " degrees Celsius" << endl;

    // Write your code here

    return 0;
}
