#ifndef CRUTHU_FORMAPERLIN_HPP
#define CRUTHU_FORMAPERLIN_HPP

#include <cruthu/IForma.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <memory>

namespace cruthu {
class FormaPerlin : public IForma {
public:
    FormaPerlin();
    ~FormaPerlin() = default;

    virtual void Modify(std::shared_ptr<cruthu::ITera> tera);
    virtual void Step(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<cruthu::Node> mNode;
    unsigned int mStepsTaken;
};

extern "C" {
	cruthu::FormaPerlin * allocator() {
		return new cruthu::FormaPerlin();
	}

	void deleter(cruthu::FormaPerlin * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
