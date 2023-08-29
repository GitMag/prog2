#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a positive number: ";

    // num to calculate factors
    int num;

    cin >> num;

    // chek if num is positive
    if (num < 1) {
        cout << "Only positive numbers accepted" << endl;
        return 0;
    }

    // valid num, continue
    //closest factors, num by default:
    int c_fac1 = num;
    int c_fac2 = num;
    int closest_fac_proximity = num;
    int fac_proximity;

    // get factor
    for (int i = 1; i <= num; i++) {

        if (num % i == 0) {
            int fac1 = num / i;
            int fac2 = i;

            // check how close factors are of eachother
            fac_proximity = fac2 - fac1;
                if (fac_proximity < closest_fac_proximity && fac_proximity > -1) {
                    // new closest fac_proximity, save these factrs
                    c_fac1 = fac1;
                    c_fac2 = fac2;
                    closest_fac_proximity = fac_proximity;

                }
        }


    }
    // print the closest factors
    cout << num << " = " << c_fac1 << " * " << c_fac2 << endl;

    // Write your code here

    return 0;
}
