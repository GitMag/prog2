#ifndef MAMMAL_HH
#define MAMMAL_HH

#include <animal.hh>


class Mammal: public Animal
{
public:
    Mammal();
    //Mammal(const std::string& moving_noise);

    void suckle(std::ostream& output) const;
};

#endif // MAMMAL_HH
