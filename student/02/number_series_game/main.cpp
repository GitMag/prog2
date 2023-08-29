#include <iostream>


int main()
{
    std::cout << "How many numbers would you like to have? ";

    int nums;
    std::cin >> nums;

    for (int i = 1; i <= nums; ++i) {


        //check if divisble by 3 and 7
        if (i % 3 == 0 && i % 7 == 0) {
            std::cout << "zip boing" << std::endl;

        // check if divisble by 3
        } else if (i % 3 == 0) {
            std::cout << "zip" << std::endl;

        // check if divisible by 7
        } else if (i % 7 == 0) {
            std::cout << "boing" << std::endl;

        // not divisible, print number
        } else {
            std::cout << i << std::endl;
        }

    }

    // Write your code here

    return 0;
}
