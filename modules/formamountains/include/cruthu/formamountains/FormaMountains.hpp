#ifndef CRUTHU_FORMAMOUNTAINS_HPP
#define CRUTHU_FORMAMOUNTAINS_HPP

#include <cruthu/IForma.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <memory>
#include <random>

namespace cruthu {
class FormaMountains : public IForma {
public:
    FormaMountains();
    ~FormaMountains() = default;

    virtual void Modify(std::shared_ptr<cruthu::ITera> tera);
    virtual void Step(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<cruthu::Node> mNode;
    unsigned int mStepsTaken;
    bool mAllMountains;
};

extern "C" {
	cruthu::FormaMountains * allocator() {
		return new cruthu::FormaMountains();
	}

	void deleter(cruthu::FormaMountains * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
