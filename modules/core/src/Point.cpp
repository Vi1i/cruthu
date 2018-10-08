#include <cruthu/Point.hpp>

#include <boost/uuid/uuid.hpp>

#include <iostream>

void Cruthu::Point::SetNeighbor(std::shared_ptr<Cruthu::Point> neighbor) {
    this->mNeighbors.push_back(neighbor);
}

bool Cruthu::Point::RemoveNeighbor(std::shared_ptr<Cruthu::Point> neighbor) {
    auto before = this->mNeighbors.size();
    this->mNeighbors.erase(std::remove_if(this->mNeighbors.begin(), this->mNeighbors.end(),
            [neighbor](std::shared_ptr<Cruthu::Point> const& ptr) {
                return ptr.get()->GetTag() == neighbor.get()->GetTag();
            }),
            this->mNeighbors.end());
    auto after = this->mNeighbors.size();
    return after < before;
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

void Cruthu::Point::operator=(Cruthu::Point const& rhs) {
    this->mTag = rhs.mTag;
    this->mNeighbors = rhs.mNeighbors;
}
