#ifndef CRUTHU_FORMARIVERS_HPP
#define CRUTHU_FORMARIVERS_HPP

#include <cruthu/IForma.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <memory>
#include <random>
#include <unordered_set>

namespace cruthu {
class FormaRivers : public IForma {
public:
    FormaRivers();
    ~FormaRivers() = default;

    virtual void Modify(std::shared_ptr<cruthu::ITera> tera);
    virtual void Step(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<cruthu::Node> mNode;
    std::unordered_set<std::string> mVisited;
    unsigned int mStepsTaken;
};

extern "C" {
	cruthu::FormaRivers * allocator() {
		return new cruthu::FormaRivers();
	}

	void deleter(cruthu::FormaRivers * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
