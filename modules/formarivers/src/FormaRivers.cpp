#include <cruthu/formarivers/FormaRivers.hpp>

#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <random>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

cruthu::FormaRivers::FormaRivers() {
    this->mSeed = std::random_device()();
    this->mStepsTaken = 0;
}

void cruthu::FormaRivers::Step(std::shared_ptr<cruthu::ITera> tera) {
    if(tera->IndexedNodes.size() < 1) {
        this->mLogger->warn("No mountains indexed");
        return;
    }
    if(this->mNode.get() == nullptr) {
        // If we are in here, that means this would be the "first" step taken
        this->mNode = tera->GetIndexedNode();
        this->mVisited.insert(this->mNode->to_string());
    }
    if(this->mNode->GetTerrain() == cruthu::Terrain::Type::WATER) {
        return;
    }

    //std::mt19937 rng;
    //rng.seed(this->mSeed);
    //rng.discard(this->mStepsTaken);

    this->mNode->SetTerrain(cruthu::Terrain::Type::RIVER);
    std::shared_ptr<cruthu::Node> lPoint = this->mNode->GetNeighbors().at(0);
    for(auto neighbor : this->mNode->GetNeighbors()) {
        auto it = this->mVisited.find(neighbor->to_string());
        if(it != this->mVisited.end()) {
            continue;
        }
        if(neighbor->GetHeight() < lPoint->GetHeight()) {
            lPoint = neighbor;
        }
    }

    this->mNode = lPoint;
    this->mVisited.insert(this->mNode->to_string());

    this->mStepsTaken++;
}

void cruthu::FormaRivers::Modify(std::shared_ptr<cruthu::ITera> tera) {
    if(tera->IndexedNodes.size() < 1) {
        this->mLogger->warn("No mountains indexed");
        return;
    }

    for(auto step = 0; step < 1000; ++step) {
        this->Step(tera);
    }
}

void cruthu::FormaRivers::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("FormaRivers", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
