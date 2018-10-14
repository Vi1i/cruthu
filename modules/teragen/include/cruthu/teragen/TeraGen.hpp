#ifndef CRUTHU_TERAGEN_HPP
#define CRUTHU_TERAGEN_HPP

#include <cruthu/ITeraGen.hpp>
#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <vector>
#include <memory>

namespace cruthu {
class TeraGen : public ITeraGen {
public:
    TeraGen() = default;
    ~TeraGen() = default;
    
    virtual void Create(std::shared_ptr<cruthu::ITera>);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<spdlog::logger> mLogger;

    void Expand(std::shared_ptr<cruthu::ITera> tera, long double level);
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

