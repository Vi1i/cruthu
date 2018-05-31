#pragma once

#ifdef _WIN32
#elif __APPLE__
	#include <glm/glm.hpp>
#elif __linux__
#endif

#include <vector>
#include <glm/glm.hpp>

namespace cruthu {
class Icosphere {
public:
	Icosphere(size_t level = 0);
	~Icosphere();

	std::vector<glm::vec3> GetIndices();
	std::vector<glm::vec3> GetColor();

private:
	std::vector<glm::vec3> _sphere;
	std::vector<glm::vec3> _color;
	std::vector<glm::vec3> _faces;

	void Recurse();
	glm::vec3 MidPoint(glm::vec3 v1, glm::vec3 v2);
};
}