#include <cruthu/teragen/TeraGen.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <iostream>
#include <iomanip>
#include <limits>
#include <chrono>

void cruthu::TeraGen::Expand(long double level) {
    double long size(std::pow(4, level));
    if(size == HUGE_VAL) {
        size = std::numeric_limits<long double>::max();
    }

    std::cout << "Size: " << size << "x" << size << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<std::vector<std::shared_ptr<cruthu::Node>>> nodes(size);
    for(auto y = 0; y < size; ++y) {
        std::cout << "\rInitializing: " << std::fixed << std::setprecision(5) << (y/size) * 100.0 << "%" << std::flush;
        std::vector<std::shared_ptr<cruthu::Node>> temp;
        temp.reserve(size);
        for(auto x = 0; x < size; ++x) {
            temp.push_back(std::shared_ptr<cruthu::Node>(new cruthu::Node()));
        }
        nodes[y] = temp;
    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "\rInitializing: 100.00%, " << elapsed.count() << "s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for(auto y = 0; y < size; ++y) {
        bool TOP = false;
        bool BOTTOM = false;
        if(y == 0) {
            TOP = true;
        }else if(y == size - 1) {
            BOTTOM = true;
        }

        std::cout << "\rConnecting: " << std::fixed << std::setprecision(5) << (y/size) * 100.0 << "%" << std::flush;
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
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "\rConnecting: 100.00%, " << elapsed.count() << "s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::cout << "\rFinding Significant Node: " << std::fixed << std::setprecision(5) << (0) * 100.0 << "%" << std::flush;
    {
        std::cout << "\rFinding Significant Node: " << std::fixed << std::setprecision(5) << (.25) * 100.0 << "%" << std::flush;
        int x = size / 2;
        std::cout << "\rFinding Significant Node: " << std::fixed << std::setprecision(5) << (.5) * 100.0 << "%" << std::flush;
        int y = size / 2;
        std::cout << "\rFinding Significant Node: " << std::fixed << std::setprecision(5) << (.75) * 100.0 << "%" << std::flush;
        this->mSignificant = nodes.at(y).at(x);
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "\rFinding Signifiant Node: 100.00%, " << elapsed.count() << "s" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    for(auto y = 0; y < size; ++y) {
        std::cout << "\rUnloading: " << std::fixed << std::setprecision(5) << (y/size) * 100.0 << "%" << std::flush;
        for(auto x = 0; x < size; ++x) {
            this->mNodes.push_back(nodes.at(y).at(x));
        }
    }
    finish = std::chrono::high_resolution_clock::now();
    elapsed = finish - start;
    std::cout << "\rUnloading: 100.00%, " << elapsed.count() << "s" << std::endl;

}

std::vector<std::shared_ptr<cruthu::Node>> cruthu::TeraGen::Create() {
    this->Expand(6);
    return this->mNodes;
}

std::shared_ptr<cruthu::Node> cruthu::TeraGen::GetSignificantNode() {
    return this->mSignificant;
}
