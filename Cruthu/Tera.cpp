#include "Tera.hpp"
#include "Point.hpp"
#include "IGenerate.hpp"

#include <memory>
#include <vector>
#include <stdexcept>

Cruthu::Tera::Tera(std::shared_ptr<Cruthu::IGenerate> generator) {
    if(generator.get() == nullptr) {
        throw std::runtime_error("Error: generator is null");
    }else{
        this->mPoints = generator.get()->Create();
    }
}

const std::vector<Cruthu::Point> & Cruthu::Tera::Points() {
    return this->mPoints;
}
