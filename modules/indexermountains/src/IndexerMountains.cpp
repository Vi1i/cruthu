#include <cruthu/indexermountains/IndexerMountains.hpp>

#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <memory>
#include <random>

void cruthu::IndexerMountains::Index(std::shared_ptr<cruthu::ITera> tera) {
    tera->IndexedNodes.clear();
    for(auto node : tera->Nodes) {
        if(node->GetTerrain() == cruthu::Terrain::Type::MOUNTAIN) {
            if(this->mLogger.get()) {
                this->mLogger->trace("Indexed Mountain: " + node->to_string());
            }
            tera->IndexedNodes.push_back(node);
        }
    }
}

void cruthu::IndexerMountains::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("IndexerMountains", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
