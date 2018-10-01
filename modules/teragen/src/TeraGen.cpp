#include <cruthu/teragen/TeraGen.hpp>

#include <iostream>

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::TeraGen::Create() {
    std::shared_ptr<Cruthu::Point> zero = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> one = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> two = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> three = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> four = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> five = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> six = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> seven = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> eight = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> nine = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> ten = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());
    std::shared_ptr<Cruthu::Point> eleven = std::shared_ptr<Cruthu::Point>(new Cruthu::Point());

    zero->SetID(0);
    zero->SetNeighbor(one);
    zero->SetNeighbor(two);
    zero->SetNeighbor(three);
    zero->SetNeighbor(four);
    zero->SetNeighbor(five);

    one->SetID(1);
    one->SetNeighbor(zero);
    one->SetNeighbor(two);
    one->SetNeighbor(five);
    one->SetNeighbor(six);
    one->SetNeighbor(seven);

    two->SetID(2);
    two->SetNeighbor(zero);
    two->SetNeighbor(one);
    two->SetNeighbor(three);
    two->SetNeighbor(seven);
    two->SetNeighbor(eight);

    three->SetID(3);
    three->SetNeighbor(zero);
    three->SetNeighbor(two);
    three->SetNeighbor(four);
    three->SetNeighbor(eight);
    three->SetNeighbor(nine);

    four->SetID(4);
    four->SetNeighbor(zero);
    four->SetNeighbor(three);
    four->SetNeighbor(five);
    four->SetNeighbor(nine);
    four->SetNeighbor(ten);

    five->SetID(5);
    five->SetNeighbor(one);
    five->SetNeighbor(zero);
    five->SetNeighbor(four);
    five->SetNeighbor(six);
    five->SetNeighbor(ten);

    six->SetID(6);
    six->SetNeighbor(one);
    six->SetNeighbor(five);
    six->SetNeighbor(seven);
    six->SetNeighbor(ten);
    six->SetNeighbor(eleven);

    seven->SetID(7);
    seven->SetNeighbor(one);
    seven->SetNeighbor(two);
    seven->SetNeighbor(six);
    seven->SetNeighbor(eight);
    seven->SetNeighbor(eleven);

    eight->SetID(8);
    eight->SetNeighbor(two);
    eight->SetNeighbor(three);
    eight->SetNeighbor(seven);
    eight->SetNeighbor(nine);
    eight->SetNeighbor(eleven);

    nine->SetID(9);
    nine->SetNeighbor(three);
    nine->SetNeighbor(four);
    nine->SetNeighbor(eight);
    nine->SetNeighbor(ten);
    nine->SetNeighbor(eleven);

    ten->SetID(10);
    ten->SetNeighbor(four);
    ten->SetNeighbor(five);
    ten->SetNeighbor(six);
    ten->SetNeighbor(nine);
    ten->SetNeighbor(eleven);

    eleven->SetID(11);
    eleven->SetNeighbor(six);
    eleven->SetNeighbor(seven);
    eleven->SetNeighbor(eight);
    eleven->SetNeighbor(nine);
    eleven->SetNeighbor(ten);

    this->mPoints.push_back(zero);
    this->mPoints.push_back(one);
    this->mPoints.push_back(two);
    this->mPoints.push_back(three);
    this->mPoints.push_back(four);
    this->mPoints.push_back(five);
    this->mPoints.push_back(six);
    this->mPoints.push_back(seven);
    this->mPoints.push_back(eight);
    this->mPoints.push_back(nine);
    this->mPoints.push_back(ten);
    this->mPoints.push_back(eleven);

    return this->mPoints;
}
