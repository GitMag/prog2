#include "giraffe.hh"


Giraffe::Giraffe() :
    Mammal()  {

}

void Giraffe::make_noise(std::ostream &output)
{
    output << "Mus mus" << std::endl;
}


