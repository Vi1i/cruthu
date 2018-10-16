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

namespace {
    cruthu::Terrain::Type Threshold(double val) {
        cruthu::Terrain::Type type;
        if(val < .4) {
            type = cruthu::Terrain::Type::WATER;
        }else if(val < .7) {
            type = cruthu::Terrain::Type::GRASSLAND;
        }else if(val < .8) {
            type = cruthu::Terrain::Type::FOREST;
        }else{
            type = cruthu::Terrain::Type::MOUNTAIN;
        }

        return type;
    }
}

void cruthu::FormaPerlin::Modify(std::shared_ptr<cruthu::ITera> tera) {
    std::mt19937 rng;
    rng.seed(std::random_device()());
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
