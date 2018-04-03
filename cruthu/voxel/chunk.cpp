#include <cruthu/voxel/chunk.hpp>

namespace cruthu::voxel {
    Chunk::Chunk() {
        this->m_pBlocks = new Block**[CHUNK_SIZE];
        for(int z = 0; z < CHUNK_SIZE; ++z) {
            this->m_pBlocks[z] = new Block*[CHUNK_SIZE];
            for(int y = 0; y < CHUNK_SIZE; ++y) {
                this->m_pBlocks[z][y] = new Block[CHUNK_SIZE];
            }
        }
    }

    Chunk::~Chunk() {
        for(int z = 0; z < CHUNK_SIZE; ++z) {
            for(int y = 0; y < CHUNK_SIZE; ++y) {
                delete [] this->m_pBlocks[z][y];
            }
            delete [] this->m_pBlocks[z];
        }
        delete [] this->m_pBlocks;
    }
}
