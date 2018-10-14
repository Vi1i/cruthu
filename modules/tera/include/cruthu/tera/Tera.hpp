#ifndef CRUTHU_TERA_HPP
#define CRUTHU_TERA_HPP

#include <cruthu/ITera.hpp>
#include <cruthu/Node.hpp>

#include <vector>
#include <memory>
#include <random>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/sink.h>

namespace cruthu {
class Tera : public ITera {
public:
    Tera() = default;
    ~Tera() = default;

    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);
    virtual std::shared_ptr<cruthu::Node> GetIndexedNode();

private:
    std::shared_ptr<spdlog::logger> mLogger;
};
extern "C" {
	cruthu::Tera * allocator() {
		return new cruthu::Tera();
	}

	void deleter(cruthu::Tera * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
