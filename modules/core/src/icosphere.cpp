#include <random>
#include <cmath>
#include <cruthu/icosphere/icosphere.hpp>

namespace cruthu {
#define X 0.525731112119133606f 
#define Z 0.850650808352039932f
#define N 0.f

	static float _vertices[12][3] = {    
		{-X, N, Z}, {X, N, Z}, {-X, N, -Z}, {X, N, -Z},    
		{N, Z, X}, {N, Z, -X}, {N, -Z, X}, {N, -Z, -X},    
		{Z, X, N}, {-Z, X, N}, {Z, -X, N}, {-Z, -X, N} 
	};
	static int _indices[20][3] = { 
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11}
	};

	Icosphere::Icosphere(size_t level) {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0, 1);

		for(auto i = 0; i < 20; ++i) {
			for(auto n = 0; n < 3; ++n) {
				float r1(dist(e2));
				float r2(dist(e2));
				float r3(dist(e2));
				this->_color.push_back(glm::vec3(r1,r2,r3));

				float x(_vertices[_indices[i][n]][0]);
				float y(_vertices[_indices[i][n]][1]);
				float z(_vertices[_indices[i][n]][2]);
				this->_sphere.push_back(glm::vec3(x,y,z));
			}
		}

		for(auto z = 0; z < level; ++z) {
			this->Recurse();
		}
	}

	Icosphere::~Icosphere() {}

	std::vector<glm::vec3> Icosphere::GetIndices() {
		return this->_sphere;
	// return this->_faces;
	}

	std::vector<glm::vec3> Icosphere::GetColor() {
		return this->_color;
	}

	void Icosphere::Recurse() {
		std::random_device rd;
		std::mt19937 e2(rd());
		std::uniform_real_distribution<> dist(0, 1);

		std::vector<glm::vec3> recurse;
		std::vector<glm::vec3> color;

		for(auto z = 0; z < this->_sphere.size(); z += 3) {
			for(auto n = 0; n < 12; ++n) {
				float r1(dist(e2));
				float r2(dist(e2));
				float r3(dist(e2));
				color.push_back(glm::vec3(r1,r2,r3));
			}
			glm::vec3 v0(this->_sphere[z]);
			glm::vec3 v1(this->_sphere[z + 1]);
			glm::vec3 v2(this->_sphere[z + 2]);
			glm::vec3 a(glm::normalize(this->MidPoint(v0, v1)));
			glm::vec3 b(glm::normalize(this->MidPoint(v1, v2)));
			glm::vec3 c(glm::normalize(this->MidPoint(v2, v0)));

			recurse.push_back(v0);
			recurse.push_back(a);
			recurse.push_back(c);
			recurse.push_back(v1);
			recurse.push_back(b);
			recurse.push_back(a);
			recurse.push_back(v2);
			recurse.push_back(b);
			recurse.push_back(c);
			recurse.push_back(a);
			recurse.push_back(b);
			recurse.push_back(c);
		// recurse.push_back(v0);
		}

		this->_color = color;
		this->_sphere = recurse;
	}

	glm::vec3 Icosphere::MidPoint(glm::vec3 v1, glm::vec3 v2) {
		float x((v1[0] + v2[0]) / 2.0);
		float y((v1[1] + v2[1]) / 2.0);
		float z((v1[2] + v2[2]) / 2.0);
		return glm::vec3(x, y, z);
	}
}
