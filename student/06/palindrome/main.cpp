#include <iostream>
#include <string>
#ifndef RECURSIVE_FUNC
#define RECURSIVE_FUNC
#endif

bool palindrome_recursive(std::string s)
{
  RECURSIVE_FUNC
  // Do not remove RECURSIVE_FUNC declaration, it's necessary for automatic testing to work
  // ------------


  // define variables
  int string_lenght = s.size();
  char string_first_letter = s.at(0);
  char string_last_letter = s.at(string_lenght-1);

  // check if string lenght is over 3 so that we can compare the first and last char
  if (string_lenght > 2) {
      // test if first and last letter are the same
      if (string_last_letter == string_first_letter) {
          // create new substring that does not contain first and last letter
          std::string shorter = s.substr(1, string_lenght-2);
          return palindrome_recursive(shorter);
      } else {
          // not identical first and last letter
          return false;
      }
  }

  // if the function has made it this far then the string must be a palindrome
  return true;
}

// Do not modify rest of the code, or the automated testing won't work.
#ifndef UNIT_TESTING
int main()
{
    std::cout << "Enter a word: ";
    std::string word;
    std::cin >> word;

    if(palindrome_recursive(word)){
        std::cout << word << " is a palindrome" << std::endl;
    } else {
        std::cout << word << " is not a palindrome" << std::endl;
    }
}
#endif
