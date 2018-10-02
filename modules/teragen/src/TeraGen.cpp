#include <cruthu/teragen/TeraGen.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <iostream>

namespace {
    std::vector<std::shared_ptr<Cruthu::Point>> Recurse(unsigned int level, const std::vector<std::shared_ptr<Cruthu::Point>>& origin) {
        std::shared_ptr<Cruthu::Point> start = origin.at(0);
        std::cout << boost::uuids::to_string(start.get()->GetTag()) << std::endl;
        for(auto const& nP : start.get()->GetNeighbors()) {
            std::cout << "\t" << nP->GetTag() << std::endl;
        }
        return origin;
    }
}

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::TeraGen::Create() {
    std::shared_ptr<Cruthu::Point> one = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> two = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> three = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> four = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> five = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> six = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> seven = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> eight = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());

    one->SetNeighbor(two);
    one->SetNeighbor(four);
    one->SetNeighbor(five);

    two->SetNeighbor(one);
    two->SetNeighbor(three);
    two->SetNeighbor(six);

    three->SetNeighbor(two);
    three->SetNeighbor(four);
    three->SetNeighbor(seven);

    four->SetNeighbor(one);
    four->SetNeighbor(three);
    four->SetNeighbor(eight);

    five->SetNeighbor(one);
    five->SetNeighbor(six);
    five->SetNeighbor(eight);

    six->SetNeighbor(two);
    six->SetNeighbor(five);
    six->SetNeighbor(seven);

    seven->SetNeighbor(three);
    seven->SetNeighbor(six);
    seven->SetNeighbor(eight);

    eight->SetNeighbor(four);
    eight->SetNeighbor(five);
    eight->SetNeighbor(seven);

    this->mPoints.push_back(one);
    this->mPoints.push_back(two);
    this->mPoints.push_back(three);
    this->mPoints.push_back(four);
    this->mPoints.push_back(five);
    this->mPoints.push_back(six);
    this->mPoints.push_back(seven);
    this->mPoints.push_back(eight);

    return Recurse(5, this->mPoints);
}
