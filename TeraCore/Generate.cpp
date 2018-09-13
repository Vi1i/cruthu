#include "Generate.hpp"

#include <iostream>

std::vector<Cruthu::Point> Cruthu::Generate::Create() {
    std::cout << "Generate::Create()" << std::endl;
    return this->mPoints;
}
// the class factories
extern "C" Cruthu::Generate * create() {
    return new Cruthu::Generate;
}

extern "C" void destroy(Cruthu::Generate * gen) {
    delete gen;
}
