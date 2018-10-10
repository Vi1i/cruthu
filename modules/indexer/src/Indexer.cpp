#include <cruthu/indexer/Indexer.hpp>

#include <vector>
#include <memory>
#include <random>

std::vector<std::shared_ptr<cruthu::Node>> cruthu::Indexer::Index(std::vector<std::shared_ptr<cruthu::Node>> nodes) {
    std::vector<std::shared_ptr<cruthu::Node>> indexedNodes;

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, nodes.size());

    for(auto pos = 0; pos <= (nodes.size() / 10); ++pos) {
        indexedNodes.push_back(nodes.at(dist(rng)));
    }

    return indexedNodes;
}

std::vector<std::shared_ptr<cruthu::Node>> cruthu::Indexer::Index(std::shared_ptr<cruthu::Node> node) {
    std::vector<std::shared_ptr<cruthu::Node>> indexedNodes;
    // TODO: (Vi1i) Implement this...
    return indexedNodes;
}
