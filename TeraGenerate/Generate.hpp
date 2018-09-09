#ifndef CRUTHU_GENERATE_HPP
#define CRUTHU_GENERATE_HPP

#include "Cruthu/IGenerate.hpp"
#include "Cruthu/Point.hpp"

#include <vector>

namespace Cruthu {
class Generate : public IGenerate {
public:
    Generate() = default;
    ~Generate() = default;
    
    virtual std::vector<Cruthu::Point> Create();


private:
    std::vector<Cruthu::Point> mPoints;
    std::vector<Cruthu::Point> mCreate();
};
extern "C" {
	Cruthu::Generate * allocator() {
		return new Cruthu::Generate();
	}

	void deleter(Cruthu::Generate * ptr) {
		delete ptr;
	}
}
} // namespace Cruthu
#endif

