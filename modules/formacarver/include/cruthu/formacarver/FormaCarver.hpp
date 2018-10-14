#ifndef CRUTHU_FORMACARVER_HPP
#define CRUTHU_FORMACARVER_HPP

#include <cruthu/IForma.hpp>
#include <cruthu/ITera.hpp>

#include <memory>

namespace cruthu {
class FormaCarver : public IForma {
public:
    FormaCarver() = default;
    ~FormaCarver() = default;

    virtual void Modify(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<spdlog::logger> mLogger;
};

extern "C" {
	cruthu::FormaCarver * allocator() {
		return new cruthu::FormaCarver();
	}

	void deleter(cruthu::FormaCarver * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
