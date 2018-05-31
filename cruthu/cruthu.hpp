#pragma once

#include <vector>
#include <glm/glm.hpp>

// http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation/
#include <cruthu/config.hpp>
#include <cruthu/icosphere/icosphere.hpp>

namespace cruthu {
    void Version();

    class  Cruthu {
    public:
    	Cruthu(size_t size);
    	~Cruthu();

    	void GenerateWorld();
   		size_t GetLevel();
   		std::vector<glm::vec3> GetPoints();


    private:
    	size_t level;
    	std::vector<glm::vec3> points;
    };
}
