#include <cruthu/tera/Tera.hpp>

#include <vector>
#include <memory>
#include <random>

void cruthu::Tera::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("Tera", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}

std::shared_ptr<cruthu::Node> cruthu::Tera::GetIndexedNode() {
    //TODO: (Vi1i) Make a better way to return an idexed node than random...
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<int> dist(0, this->IndexedNodes.size() - 1);
    int index = dist(rng);

    if(this->mLogger.get()) {
        this->mLogger->trace(this->IndexedNodes.at(index)->to_string());
    }

    return this->IndexedNodes.at(index);
}
