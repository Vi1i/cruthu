#pragma once

#include <vector>
#include <glm/glm.hpp>

// http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
//#include <cruthu/config.hpp>
//#include <cruthu/icosphere/icosphere.hpp>

namespace cruthu {
    void Version();

    class  Cruthu {
    public:
    	Cruthu() = default;
    	~Cruthu() = default;

        void Initialize();
    private:
    };
}
