#include <cruthu/formaperlin/FormaPerlin.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include "PerlinNoise.hpp"

#include <random>
#include <memory>
#include <climits>
#include <limits>
#include <unordered_set>
#include <stack>
#include <deque>
#include <string>

namespace {
    cruthu::Terrain::Type Threshold(double val) {
        cruthu::Terrain::Type type;
        if(val < .58) {
            type = cruthu::Terrain::Type::WATER;
        }else if(val < .7) {
            type = cruthu::Terrain::Type::GRASSLAND;
        }else if(val < .79) {
            type = cruthu::Terrain::Type::FOREST;
        }else{
            type = cruthu::Terrain::Type::MOUNTAIN;
        }

        return type;
    }

    std::string Threshold_Name(double val) {
        std::string name;
        if(val < .58) {
            name = "WATER";
        }else if(val < .7) {
            name = "GRASSLAND";
        }else if(val < .79) {
            name = "FOREST";
        }else{
            name = "MOUNTAIN";
        }

        return name;
    }
}

cruthu::FormaPerlin::FormaPerlin() {
    this->mSeed = std::random_device()();
    this->mStepsTaken = 0;
}

void cruthu::FormaPerlin::Step(std::shared_ptr<cruthu::ITera> tera) {
    std::string stepStr("[" + std::to_string(this->mSeed) + "].[" + std::to_string(this->mStepsTaken) + "]");
    std::mt19937 rng;
    rng.seed(this->mSeed);
    std::uniform_int_distribution<int> distSeed(0, std::numeric_limits<int>::max());
    utils::PerlinNoise pn(this->mSeed);

    int y = this->mStepsTaken / tera->YSize;
    int x = this->mStepsTaken - (y * tera->YSize);
    int pos = (y * tera->YSize) + x;
    double Y = (double) y / (double)tera->YSize;
    double X = (double) x / (double)tera->XSize;
    double val = pn.Noise(10 * X, 10 * Y, .8);
    tera->Nodes.at(pos)->SetTerrain(Threshold(val));
    this->mLogger->trace(stepStr + ".(" + std::to_string(x) + "," + std::to_string(y) + ").[" + 
                         tera->Nodes.at(pos)->to_string() + "].[" + std::to_string(val) +
                         + "].[" + Threshold_Name(val) + "]");
    ++this->mStepsTaken;
}

void cruthu::FormaPerlin::Modify(std::shared_ptr<cruthu::ITera> tera) {
    std::mt19937 rng;
    rng.seed(this->mSeed);
    std::uniform_int_distribution<int> distSeed(0, std::numeric_limits<int>::max());
    this->mLogger->debug("Created distributions");

    unsigned int seed = distSeed(rng);
    this->mLogger->trace("Perlin's Noise seed: " + std::to_string(seed));
    utils::PerlinNoise pn(seed);
    this->mLogger->debug("Perlin's Noise generator created");
    for(auto y = 0; y < tera->YSize; ++y) {
        double Y = (double) y / (double)tera->YSize;
        for(auto x = 0; x < tera->XSize; ++x) {
            double X = (double) x / (double)tera->XSize;
            tera->Nodes.at((y * tera->YSize) + x)->SetTerrain(Threshold(pn.Noise(10 * X, 10 * Y, 0.8)));
        }
    }
}

void cruthu::FormaPerlin::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("FormaPerlin", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
