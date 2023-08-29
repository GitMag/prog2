#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // check word lenght, only shuffle if lenght is over 2
        if (word.size() > 2) {

            // get first letter and last letter
            char first = word.at(0);
            char last =  word.at(word.size()-1);

            //remove first and last letter from word
            std::string random_part = word.substr(1, word.size()-2);
            std::shuffle(random_part.begin(), random_part.end(), generator);
            random_part.insert(random_part.begin(), first);
            random_part.insert(random_part.end(), last);

            word = random_part;
        }

        std::cout << word << std::endl;
    }
}
