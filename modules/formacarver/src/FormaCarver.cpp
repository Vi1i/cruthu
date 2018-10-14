#include <cruthu/formacarver/FormaCarver.hpp>
#include <cruthu/ITera.hpp>

#include <random>
#include <memory>
#include <climits>

void cruthu::FormaCarver::Modify(std::shared_ptr<cruthu::ITera> tera) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist;
    std::uniform_real_distribution<double> height;
    std::uniform_int_distribution<std::mt19937::result_type> mode(0, 1);
    double mod;
    if((mode(rng) % 2) == 0) {
        mod = -1.0;
        dist = std::uniform_int_distribution<std::mt19937::result_type>(10000, 100000);
        height = std::uniform_real_distribution<double>(0.0,0.1);
    }else{
        dist = std::uniform_int_distribution<std::mt19937::result_type>(1000, 10000);
        height = std::uniform_real_distribution<double>(0.0,0.2);
        mod = 1.0;
    }

    int maxSteps = dist(rng);
    std::shared_ptr<cruthu::Node> curNode = tera->GetIndexedNode();
    if(this->mLogger.get()) {
        this->mLogger->trace("IndexedNode: " + curNode->to_string());
    }


    for(auto step = 0; step < maxSteps; ++step) {
        std::uniform_int_distribution<std::mt19937::result_type> direction(0, curNode->GetNeighbors().size() - 1);
        double modHeight = height(rng);
        double curHeight = curNode->GetHeight();
        double newHeight;
        if((curHeight + (mod * modHeight)) < 0.0) {
            newHeight = 0.0;
        }else if((curHeight + (mod * modHeight)) > 1.0) {
            newHeight = 1.0;
        }else{
            newHeight = curHeight + (mod * modHeight);
        }
        int dir = direction(rng);
        if(this->mLogger.get()) {
            this->mLogger->trace("(" + std::to_string(step) + ") " + curNode->to_string() + " carved to " + std::to_string(newHeight));
            this->mLogger->trace("(" + std::to_string(step) + ") Stepping to " + curNode->GetNeighbors().at(dir)->to_string());
        }
        curNode->SetHeight(newHeight);
        curNode = curNode->GetNeighbors().at(dir);
    }

}

void cruthu::FormaCarver::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("FormaCarver", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
