#include <cruthu/tera/Tera.hpp>

#include <vector>
#include <memory>
#include <random>

void Cruthu::Tera::SetIndexer(std::shared_ptr<Cruthu::IIndexer> indexer) {
    this->mIndexer = indexer;
}

void Cruthu::Tera::IndexPoints() {
    this->mIndexedPoints = this->mIndexer.get()->Index(this->mPoints);
}

const std::vector<std::shared_ptr<Cruthu::Point>> & Cruthu::Tera::GetPoints() {
    return this->mPoints;
}

std::shared_ptr<Cruthu::Point> Cruthu::Tera::GetIndexedPoint() {
    //TODO: (Vi1i) Make a better way to return an idexed point than random...
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->mIndexedPoints.size());

    return this->mIndexedPoints.at(dist(rng));
}
