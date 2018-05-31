#include <iostream>
#include <random>

#include <cruthu/cruthu.hpp>

namespace cruthu {
    void Version() {
        std::cout << "Version: " << CRUTHU_VERSION_STRING << std::endl;
    }

    Cruthu::Cruthu(size_t level) {
    	this->level = level;
    }

    Cruthu::~Cruthu() {
    }

    void Cruthu::GenerateWorld() {
    }

    size_t Cruthu::GetLevel() {
        return this->level;
    }

    std::vector<glm::vec3> Cruthu::GetPoints() {
    }
}
