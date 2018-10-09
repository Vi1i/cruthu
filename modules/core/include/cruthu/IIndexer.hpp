#ifndef CRUTHU_IINDEXER_HPP
#define CRUTHU_IINDEXER_HPP

#include <cruthu/Point.hpp>

#include <memory>
#include <vector>

namespace Cruthu {
class IIndexer {
public:
    virtual ~IIndexer() = 0;
    virtual std::vector<std::shared_ptr<Cruthu::Point>> Index(std::shared_ptr<Cruthu::Point> point) = 0;
    virtual std::vector<std::shared_ptr<Cruthu::Point>> Index(std::vector<std::shared_ptr<Cruthu::Point>> points) = 0;
};
} // namespace Cruthu
#endif
