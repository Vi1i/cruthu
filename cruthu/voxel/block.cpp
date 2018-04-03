#include <cruthu/voxel/block.hpp>

namespace cruthu::voxel {
    Block::Block() {
        this->m_active = false;
    }

    Block::~Block() {
    }

    bool Block::IsActive() {
    	return this->m_active;
    }

    void Block::SetType(Type type) {
        this->m_type = type;
    }

    void Block::SetActive(bool active) {
    	this->m_active = active;
    }
}
