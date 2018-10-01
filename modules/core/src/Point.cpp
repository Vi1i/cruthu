#include <cruthu/Point.hpp>

void Cruthu::Point::SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor) {
    this->mNeighbors.push_back(neighbor);
}

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::Point::GetNeighbors() {
    return this->mNeighbors;
}

boost::uuids::uuid Cruthu::Point::GetTag() {
    return this->mTag;
}

bool Cruthu::Point::operator==(Cruthu::Point const& rhs) const {
    return this->mTag == rhs.mTag;
}
