#pragma once

#include <cruthu/voxel/block.hpp>

namespace cruthu::voxel {
    class Chunk {
    public:
        Chunk();
        ~Chunk();

        void Update(float dt);

        void Render();

        static const int CHUNK_SIZE = 16;

    private:
        Block *** m_pBlocks;
    };
}
