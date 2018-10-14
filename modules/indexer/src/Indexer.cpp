#include <cruthu/indexer/Indexer.hpp>

#include <cruthu/ITera.hpp>

#include <memory>
#include <random>

void cruthu::Indexer::Index(std::shared_ptr<cruthu::ITera> tera) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, tera->Nodes.size() - 1);

    for(auto pos = 0; pos <= (tera->Nodes.size() / 100); ++pos) {
        int index = dist(rng);
        if(this->mLogger.get()) {
            this->mLogger->trace(tera->Nodes.at(index)->to_string());
        }
        tera->IndexedNodes.push_back(tera->Nodes.at(index));
    }
}

void cruthu::Indexer::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("Indexer", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
