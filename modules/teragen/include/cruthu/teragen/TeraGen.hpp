#ifndef CRUTHU_TERAGEN_HPP
#define CRUTHU_TERAGEN_HPP

#include <cruthu/ITeraGen.hpp>
#include <cruthu/Node.hpp>

#include <vector>

namespace cruthu {
class TeraGen : public ITeraGen {
public:
    TeraGen() = default;
    ~TeraGen() = default;
    
    virtual std::vector<std::shared_ptr<cruthu::Node>> Create();
    virtual std::shared_ptr<cruthu::Node> GetSignificantNode();

private:
    std::vector<std::shared_ptr<cruthu::Node>> mNodes;
    std::shared_ptr<cruthu::Node> mSignificant;

    void Expand(long double level);
};
extern "C" {
	cruthu::TeraGen * allocator() {
		return new cruthu::TeraGen();
	}

	void deleter(cruthu::TeraGen * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif

