#ifndef CRUTHU_TERAGEN_HPP
#define CRUTHU_TERAGEN_HPP

#include <cruthu/IGenerate.hpp>
#include <cruthu/Point.hpp>

#include <vector>

namespace Cruthu {
class TeraGen : public IGenerate {
public:
    TeraGen() = default;
    ~TeraGen() = default;
    
    virtual std::vector<std::shared_ptr<Cruthu::Point>> Create();
    virtual std::shared_ptr<Cruthu::Point> GetSignificantPoint();

private:
    std::vector<std::shared_ptr<Cruthu::Point>> mPoints;
    std::shared_ptr<Cruthu::Point> mSignificant;

    void Expand(long double level);
};
extern "C" {
	Cruthu::TeraGen * allocator() {
		return new Cruthu::TeraGen();
	}

	void deleter(Cruthu::TeraGen * ptr) {
		delete ptr;
	}
}
} // namespace Cruthu
#endif

