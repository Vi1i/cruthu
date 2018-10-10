#include <cruthu/tera/Tera.hpp>

#include <vector>
#include <memory>
#include <random>

void cruthu::Tera::SetIndexer(std::shared_ptr<cruthu::IIndexer> indexer) {
    this->mIndexer = indexer;
}

void cruthu::Tera::SetNodes(std::vector<std::shared_ptr<cruthu::Node>> nodes) {
    if(this->mNodesSet) {
        return;
    }
    
    this->mNodesSet = true;
    this->mNodes = nodes;
}

void cruthu::Tera::IndexNodes() {
    if(this->mNodesSet) {
        this->mIndexedNodes = this->mIndexer.get()->Index(this->mSignificant);
    }else{
        this->mIndexedNodes = this->mIndexer.get()->Index(this->mNodes);
    }
}

const std::vector<std::shared_ptr<cruthu::Node>> & cruthu::Tera::GetNodes() {
    return this->mNodes;
}

std::shared_ptr<cruthu::Node> cruthu::Tera::GetIndexedNode() {
    //TODO: (Vi1i) Make a better way to return an idexed node than random...
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, this->mIndexedNodes.size());

    return this->mIndexedNodes.at(dist(rng));
}
