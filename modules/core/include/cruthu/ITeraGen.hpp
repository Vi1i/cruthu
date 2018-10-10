#ifndef CRUTHU_ITERAGEN_HPP
#define CRUTHU_ITERAGEN_HPP

#include <cruthu/Node.hpp>

#include <vector>

namespace cruthu {
class ITeraGen {
public:
    virtual ~ITeraGen() = default;

    virtual std::vector<std::shared_ptr<cruthu::Node>> Create() = 0;
    virtual std::shared_ptr<cruthu::Node> GetSignificantNode() = 0;
};
} // namespace cruthu
#endif

