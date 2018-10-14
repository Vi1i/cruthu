#ifndef CRUTHU_INDEXER_HPP
#define CRUTHU_INDEXER_HPP

#include <cruthu/IIndexer.hpp>
#include <cruthu/ITera.hpp>

#include <memory>
#include <random>

namespace cruthu {
class Indexer : public IIndexer {
public:
    Indexer() = default;
    ~Indexer() = default;

    virtual void Index(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<spdlog::logger> mLogger;
};

extern "C" {
	cruthu::Indexer * allocator() {
		return new cruthu::Indexer();
	}

	void deleter(cruthu::Indexer * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
