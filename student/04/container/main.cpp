#include <cstdlib>
#include <iostream>
#include <vector>


// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        // add new int to vector
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values(const std::vector <int>& ints) {
    int previous = -999;
    for (int i : ints) {
        //std::cout << previous << std::endl << i << std::endl;
        if (previous != -999) {
            // has been looped
            if (i != previous) {
                // not the same int
                return false;
            } else {

            }
        }
        // set previous val to current int i
        previous = i;
    }
    // all ints are same, return true
    return true;
}

bool is_ordered_non_strict_ascending(const std::vector <int>& ints) {
    int previous = -99999999;
    for (int i : ints) {
        //std::cout << previous << std::endl << i << std::endl;
        if (previous != -99999999) {
            // has been looped
            if (i < previous) {
                // its are not in order, return false
                return false;
            } else {

            }
        }
        // set previous val to current int i
        previous = i;
    }
    // ints are in order return true
    return true;
}

bool is_arithmetic_series(const std::vector <int>& ints) {
    int index = 0; // helper var
    int previous = 0;
    int previous_dif = 0;
    int current_dif = 0;


    for (int i : ints) {
        //std::cout << "index: " << index << std::endl;
        if (index == 0) {
            previous = i;
        } else if (index == 1) {
            previous_dif = i - previous;
        }

        if (index > 0) {
            current_dif = i - previous;
           //std::cout << "current: " << current_dif << std::endl;
           // std::cout << "previous: " << previous_dif << std::endl;

            // check difference
            if (current_dif != previous_dif) {
                // not the same differnce, cannot be arithmetic
                return false;
            } else {
                // is the same difference
                previous_dif = current_dif;
                previous = i;
            }
            // increment helper var
        }
        ++index;
    }
    // end of loop, if not false then must be true
    return true;
}

bool is_geometric_series(const std::vector <int>& ints) {
    int index = 0; // helper var
    int previous = 0;
    int previous_dif = 0;
    int current_dif = 0;


    for (int i : ints) {
        //std::cout << "index: " << index << std::endl;
        if (index == 0) {
            previous = i;
        } else if (index == 1) {
            previous_dif = i / previous;
        }

        if (index > 0) {
            current_dif = i / previous;
           //std::cout << "current: " << current_dif << std::endl;
           // std::cout << "previous: " << previous_dif << std::endl;

            // check difference
            if (current_dif != previous_dif) {
                // not the same differnce, cannot be arithmetic
                return false;
            } else {
                // is the same difference
                previous_dif = current_dif;
                previous = i;
            }
            // increment helper var

            //chek for 0
            }
        if (previous == 0) {
            return false;
        }
        ++index;
    }
    // end of loop, if not false then must be true
    return true;
}
int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
