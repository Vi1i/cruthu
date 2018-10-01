#include <cruthu/Point.hpp>

void Cruthu::Point::SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor) {
    this->mNeighbors.push_back(neighbor);
}

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::Point::GetNeighbors() {
        return this->mNeighbors;
}

unsigned int Cruthu::Point::GetID() {
    return this->mID;
}

void Cruthu::Point::SetID(unsigned int id) {
    this->mID = id;
}
