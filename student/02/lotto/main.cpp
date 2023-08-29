#include <iostream>

using namespace std;

bool check_input(int balls, int drawn_balls)
{
    if (balls < 0) {
        cout << "The number of balls must be a positive number." << endl;
        return false;
    } else if (drawn_balls > balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return false;
    } else {
        // all is valid, return true
        return true;
    }
}

unsigned long int factorial(int num)
{

    unsigned long int fac_product = 1;
    for (int i = 1; i <= num; ++i) {
        fac_product *= i;
        //cout << fac_product << endl;
    }
    return fac_product;
}

unsigned long int possible_combinations(int balls, int drawn_balls)
{
    unsigned long int fac_balls = factorial(balls);
    unsigned long int fac_drawn_balls = factorial(drawn_balls);
    unsigned long int fac_difference = factorial(balls - drawn_balls);

    return fac_balls / (fac_difference * fac_drawn_balls);
}

int main()
{
    // init values:
    int balls;
    int drawn_balls;

    // get ball amount
    cout << "Enter the total number of lottery balls: ";
    cin >> balls;

    // get drawn ball amount
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;

    // check if input is valid
    if (check_input(balls, drawn_balls) == true) {
        // valid input, do calculation
         cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << possible_combinations(balls, drawn_balls) << endl;
        }
    return 0;
}

