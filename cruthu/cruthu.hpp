#pragma once

// http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
#include <cruthu/config.hpp>
#include <cruthu/voxel/block.hpp>

namespace cruthu {
    void Version();

    class  Cruthu {
    public:
    	Cruthu(size_t size);
    	~Cruthu();

    	void GenerateWorld();
   		size_t GetSize();
   		cruthu::voxel::Block *** GetWorld();


    private:
    	size_t m_size;
    	cruthu::voxel::Block *** m_blocks;
    };
}
