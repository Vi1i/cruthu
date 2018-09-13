#ifndef CRUTHU_ITERA_HPP
#define CRUTHU_ITERA_HPP

#include "Cruthu/IIndexer.hpp"
#include "Point.hpp"

#include <memory>
#include <vector>

namespace Cruthu {
class ITera {
public:
    virtual ~ITera() = 0;

    virtual void SetIndexer(std::shared_ptr<Cruthu::IIndexer> indexer) = 0;
    virtual void IndexPoints() = 0;
    virtual const std::vector<std::shared_ptr<Cruthu::Point>> & GetPoints() = 0;
    virtual std::shared_ptr<Cruthu::Point> GetIndexedPoint() = 0;
};
} // namespace Cruthu
#endif
