#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a number: ";

    // get num
    int num;
    cin >> num;

    // cube number
    int cubed_num = num * num * num;

    // check if cubed num is valid

    if (cubed_num < 0 || cubed_num < num) {
        cout << "Error! The cube of " << num << " is not " << cubed_num << "." << endl;
    } else {
        // is valid, display cube
        cout << "The cube of " << num << " is " << cubed_num << "." << endl;
    }



}
