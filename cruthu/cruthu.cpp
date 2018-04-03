#include <iostream>
#include <random>

#include <cruthu/cruthu.hpp>

namespace cruthu {
    void Version() {
        std::cout << "Version: " << CRUTHU_VERSION_STRING << std::endl;
    }

    Cruthu::Cruthu(size_t size) {
    	this->m_size = size;
    }

    Cruthu::~Cruthu() {
        for(int z = 0; z < this->m_size; ++z) {
            for(int y = 0; y < this->m_size; ++y) {
                delete [] this->m_blocks[z][y];
            }
            delete [] this->m_blocks[z];
        }
        delete [] this->m_blocks;
    }

    void Cruthu::GenerateWorld() {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1,6);

        this->m_blocks = new cruthu::voxel::Block**[this->m_size];
        for(int x = 0; x < this->m_size; ++x) {
            this->m_blocks[x] = new cruthu::voxel::Block*[this->m_size];
            for(int y = 0; y < this->m_size; ++y) {
                this->m_blocks[x][y] = new cruthu::voxel::Block[this->m_size];
                for(int z = 0; z < this->m_size; ++z) {
                    if(dist(rng) < 5) {
                        this->m_blocks[x][y][z].SetActive(true);
                    }
                }
            }
        }
    }

    size_t Cruthu::GetSize() {
        return this->m_size;
    }

    cruthu::voxel::Block *** Cruthu::GetWorld() {
        return this->m_blocks;
    }
}
