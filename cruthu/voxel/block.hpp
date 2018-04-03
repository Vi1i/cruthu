#pragma once

#include <cruthu/voxel/type.hpp>

namespace cruthu::voxel {
    class Block {
    public:
        Block();
        ~Block();

        bool IsActive();
        void SetActive(bool active);
        void SetType(Type type);

    private:
        bool m_active;
        Type m_type;
    };
}
