#include <cruthu/teragen/TeraGen.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>

void cruthu::TeraGen::Expand(std::shared_ptr<cruthu::ITera> tera, long double level) {
    double long size(std::pow(4, level));
    if(size == HUGE_VAL) {
        size = std::numeric_limits<long double>::max();
    }

    std::vector<std::vector<std::shared_ptr<cruthu::Node>>> nodes(size);
    for(auto y = 0; y < size; ++y) {
        std::vector<std::shared_ptr<cruthu::Node>> temp;
        temp.reserve(size);
        for(auto x = 0; x < size; ++x) {
            temp.push_back(std::shared_ptr<cruthu::Node>(new cruthu::Node()));
        }
        nodes[y] = temp;
    }

    for(auto y = 0; y < size; ++y) {
        bool TOP = false;
        bool BOTTOM = false;
        if(y == 0) {
            TOP = true;
        }else if(y == size - 1) {
            BOTTOM = true;
        }

        for(auto x = 0; x < size; ++x) {
            bool LEFT = false;
            bool RIGHT = false;
            if(x == 0) {
                LEFT = true;
            }else if(x == size - 1) {
                RIGHT = true;
            }

            std::shared_ptr<cruthu::Node> cur(nodes[y][x]);
            if(TOP && LEFT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
            }else if(TOP && RIGHT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
            }else if(BOTTOM && LEFT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }else if(BOTTOM && RIGHT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }else if(TOP) {
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
            }else if(BOTTOM) {
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }else if(LEFT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }else if(RIGHT) {
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }else{
                cur.get()->SetNeighbor(nodes.at(y).at(x - 1));
                cur.get()->SetNeighbor(nodes.at(y).at(x + 1));
                cur.get()->SetNeighbor(nodes.at(y + 1).at(x));
                cur.get()->SetNeighbor(nodes.at(y - 1).at(x));
            }
            cur->SetHeight(0.5);
        }
    }

    for(auto y = 0; y < size; ++y) {
        for(auto x = 0; x < size; ++x) {
            tera->Nodes.push_back(nodes.at(y).at(x));
        }
    }
}

void cruthu::TeraGen::Create(std::shared_ptr<cruthu::ITera> tera) {
    this->Expand(tera, 5);
}

void cruthu::TeraGen::SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level) {
    this->mLogger = std::make_shared<spdlog::logger>("TeraGen", sink);
    this->mLogger->set_level(level);
    this->mLogger->trace("Logger Initilized");
}
