#include <cruthu/formamountains/FormaMountains.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <random>
#include <memory>

void cruthu::FormaMountains::Modify(std::shared_ptr<cruthu::ITera> tera) {
    bool allMountains(true);
    std::mt19937 rng;
    rng.seed(std::random_device()());
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
