#include <cruthu/formamountains/FormaMountains.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <random>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>
#include <utility>

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

    std::uniform_real_distribution<double> height(.81,1.0);

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
    std::uniform_real_distribution<double> height(.81,1.0);

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
    std::unordered_map<std::string, std::shared_ptr<cruthu::Node>> nodesA;
    for(auto node : tera->IndexedNodes) {
        nodesA[node->to_string()] = node;
        node->SetHeight(height(rng));
    }

    auto itNode = nodesA.begin();
    auto curNode = itNode->second;
    nodesA.erase(itNode);

    std::vector<std::unordered_map<std::string, std::shared_ptr<cruthu::Node>>> nodeLocalities;
    for(;;) {
        std::unordered_map<std::string, std::shared_ptr<cruthu::Node>> nodesL;
        std::unordered_map<std::string, std::shared_ptr<cruthu::Node>> nodesNV;
    

        for(;;) {
            nodesL[curNode->to_string()] = curNode;
            for(auto neighborNode : curNode->GetNeighbors()) {
                if(neighborNode->GetTerrain() != cruthu::Terrain::Type::MOUNTAIN) {
                    // Ignore
                    continue;
                }

                itNode = nodesL.find(neighborNode->to_string());
                if(itNode == nodesL.end()) {
                    // Add it to nodesNV
                    itNode = nodesNV.find(neighborNode->to_string());
                    if(itNode == nodesNV.end()) {
                        // We haven't already added it
                        nodesNV[neighborNode->to_string()] = neighborNode;
                    }
                }
            }

            if(nodesNV.empty()) {
                // No more nodes to visit
                break;
            }
            itNode = nodesNV.begin();
            curNode = itNode->second;
            nodesNV.erase(itNode);
        }

        this->mLogger->debug("Locality found, size: " + std::to_string(nodesL.size()));
        for(const auto nl : nodesL) {
            itNode = nodesA.find(nl.first);
            if(itNode != nodesA.end()) {
                nodesA.erase(itNode);
            }
        }
        nodeLocalities.push_back(nodesL);

        if(nodesA.empty()) {
            break;
        }
        itNode = nodesA.begin();
        curNode = itNode->second;
        nodesA.erase(itNode);
    };

    // nodeLocalites holds the found mountain ranges
    this->mLogger->debug("Localities found: " + std::to_string(nodeLocalities.size()));
    for(const auto locality : nodeLocalities) {
        double height(1.0);
        double mod(height/locality.size());
        unsigned int pos(0);
        //for(const auto node : locality) {
        //    node.second->SetHeight(height - (mod * pos));
        //    ++pos;
        //}
        for(auto normalize = 0; normalize < 1; ++normalize) {
            for(const auto node : locality) {
                unsigned int count(1);
                height = node.second->GetHeight();
                for(const auto neighbor : node.second->GetNeighbors()) {
                    height += neighbor->GetHeight();
                    ++count;
                }
                node.second->SetHeight(height / count);
            }
        }
    }

}

void cruthu::FormaMountains::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("FormaMountains", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
