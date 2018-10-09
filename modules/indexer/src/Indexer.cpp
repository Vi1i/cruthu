#include <cruthu/indexer/Indexer.hpp>

#include <vector>
#include <memory>
#include <random>

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::Indexer::Index(std::vector<std::shared_ptr<Cruthu::Point>> points) {
    std::vector<std::shared_ptr<Cruthu::Point>> indexedPoints;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, points.size());

    for(auto pos = 0; pos <= (points.size() / 10); ++pos) {
        indexedPoints.push_back(points.at(dist(rng)));
    }

    return indexedPoints;
}

std::vector<std::shared_ptr<Cruthu::Point>> Cruthu::Indexer::Index(std::shared_ptr<Cruthu::Point> point) {
    std::vector<std::shared_ptr<Cruthu::Point>> indexedPoints;
    // TODO: (Vi1i) Implement this...
    return indexedPoints;
}
