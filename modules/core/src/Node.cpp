#include <cruthu/Node.hpp>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>

void cruthu::Node::SetNeighbor(std::shared_ptr<cruthu::Node> neighbor) {
    this->mNeighbors.push_back(neighbor);
}

bool cruthu::Node::RemoveNeighbor(std::shared_ptr<cruthu::Node> neighbor) {
    auto before = this->mNeighbors.size();
    this->mNeighbors.erase(std::remove_if(this->mNeighbors.begin(), this->mNeighbors.end(),
            [neighbor](std::shared_ptr<cruthu::Node> const& ptr) {
                return ptr.get()->GetTag() == neighbor.get()->GetTag();
            }),
            this->mNeighbors.end());
    auto after = this->mNeighbors.size();
    return after < before;
}

std::vector<std::shared_ptr<cruthu::Node>> cruthu::Node::GetNeighbors() {
    return this->mNeighbors;
}

boost::uuids::uuid cruthu::Node::GetTag() {
    return this->mTag;
}

bool cruthu::Node::operator==(cruthu::Node const& rhs) const {
    return this->mTag == rhs.mTag;
}

void cruthu::Node::operator=(cruthu::Node const& rhs) {
    this->mTag = rhs.mTag;
    this->mNeighbors = rhs.mNeighbors;
}

void cruthu::Node::SetHeight(double height) {
    this->mHeight = height;
}

double cruthu::Node::GetHeight() {
    return this->mHeight;
}

std::string cruthu::Node::to_string() {
    return boost::uuids::to_string(this->mTag);
}

void cruthu::Node::SetTerrain(cruthu::Terrain::Type type) {
    this->mTerrain = type;
}

cruthu::Terrain::Type cruthu::Node::GetTerrain() {
    return this->mTerrain;
}
