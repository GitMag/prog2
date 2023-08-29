#include <iostream>
#include <cctype>

using namespace std;

string encrypt_text(string plaintext, string key)
{
   string encrypted_text;

   // loop trough all the chars in plaintext
   for (string::size_type i = 0; i < plaintext.length(); ++i) {
       // convert plaintext char to char from key lookup string with same order number
       int letter_nr = static_cast< int >(plaintext.at(i)) - static_cast< int >('a');
       encrypted_text += key.at(letter_nr);
   }
   return encrypted_text;
}

int main()
{

    // init required values
    string plaintext;
    string key;

    cout << "Enter the encryption key: ";
    getline(cin, key);

    // check that the key only contains lower case letters:
    for (string::size_type i = 0; i < key.length(); ++i) {
        if (islower(key.at(i) ) == false) {
            cout << "Error! The encryption key must contain only lower case characters.";
            return 1;
        }
    }

    //check if the key lenght is 26
    if (key.length() != 26) {
        cout << "Error! The encryption key must contain 26 characters.";
        return 1;
    }

    // check that the key contains all letters a-z
    string:: size_type l_pos;
    for (char letter = 'a'; letter < 'z'; ++letter) {
        l_pos = key.find(letter);

        if (l_pos == string::npos) {
            // invalid key, display error and return
            cout << "Error! The encryption key must contain all alphabets a-z.";
            return 1;
        }
    }


    // valid key, continue with encryption, enter phrase
    cout << "Enter the text to be encrypted: ";
    getline(cin, plaintext);

    // check that the plaintext only contains lower case letters
    for (string::size_type i = 0; i < plaintext.length(); ++i) {
        if (islower(plaintext.at(i) ) == false) {
            cout << "Error! The text to be encrypted must contain only lower case characters.";
            return 1;
        }
    }

    // encrypt the text
    cout << "Encrypted text: " << encrypt_text(plaintext, key) << endl;

    return 0;
}
