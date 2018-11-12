#include <cruthu/formamountains/FormaMountains.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <random>
#include <memory>

cruthu::FormaMountains::FormaMountains() {
    this->mSeed = std::random_device()();
    this->mAllMountains = true;
    this->mStepsTaken = 0;
}

void cruthu::FormaMountains::Step(std::shared_ptr<cruthu::ITera> tera) {
    if(tera->IndexedNodes.size() < 1) {
        this->mLogger->warn("No mountains indexed");
        return;
    }
    if(this->mNode.get() == nullptr) {
        // If we are in here, that means this would be the "first" step taken
        this->mNode = tera->GetIndexedNode();
        for(auto node : tera->IndexedNodes) {
            if(node->GetTerrain() != cruthu::Terrain::Type::MOUNTAIN) {
                if(this->mLogger.get()) {
                    this->mLogger->warn("Node is not a mountain, FormaMountains requires all indexed nodes to be a mountain");
                    this->mLogger->warn("Exiting FormaMountains without modifying any nodes");
                }
                this->mAllMountains = false;
                break;
            }
        }

    }

    if(!this->mAllMountains) {
        return;
    }

    std::mt19937 rng;
    rng.seed(this->mSeed);
    rng.discard(this->mStepsTaken);

    std::uniform_real_distribution<double> height(0,1);

    this->mNode->SetHeight(height(rng));
    if(this->mStepsTaken < tera->IndexedNodes.size()) {
        this->mNode = tera->IndexedNodes.at(this->mStepsTaken);
    }

    this->mStepsTaken++;
}

void cruthu::FormaMountains::Modify(std::shared_ptr<cruthu::ITera> tera) {
    if(tera->IndexedNodes.size() < 1) {
        this->mLogger->warn("No mountains indexed");
        return;
    }
    bool allMountains(true);
    std::mt19937 rng;
    rng.seed(this->mSeed);
    std::uniform_real_distribution<double> height(0,1);
    for(auto node : tera->IndexedNodes) {
        if(node->GetTerrain() != cruthu::Terrain::Type::MOUNTAIN) {
            if(this->mLogger.get()) {
                this->mLogger->warn("Node is not a mountain, FormaMountains requires all indexed nodes to be a mountain");
                this->mLogger->warn("Exiting FormaMountains without modifying any nodes");
            }
            allMountains = false;
            break;
        }
    }

    if(!allMountains) {
        return;
    }
    for(auto node : tera->IndexedNodes) {
        node->SetHeight(height(rng));
    }
}

void cruthu::FormaMountains::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("FormaMountains", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
