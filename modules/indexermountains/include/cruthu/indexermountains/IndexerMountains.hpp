#ifndef CRUTHU_INDEXERMOUNTAINS_HPP
#define CRUTHU_INDEXERMOUNTAINS_HPP

#include <cruthu/IIndexer.hpp>
#include <cruthu/ITera.hpp>

#include <memory>
#include <random>

namespace cruthu {
class IndexerMountains : public IIndexer {
public:
    IndexerMountains() = default;
    ~IndexerMountains() = default;

    virtual void Index(std::shared_ptr<cruthu::ITera> tera);
    virtual void SetSink(std::shared_ptr<spdlog::sinks::sink> sink, spdlog::level::level_enum level);

private:
    std::shared_ptr<spdlog::logger> mLogger;
};

extern "C" {
	cruthu::IndexerMountains * allocator() {
		return new cruthu::IndexerMountains();
	}

	void deleter(cruthu::IndexerMountains * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
