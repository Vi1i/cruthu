#ifndef CRUTHU_IGENERATE_HPP
#define CRUTHU_IGENERATE_HPP

#include <cruthu/Point.hpp>

#include <vector>

namespace Cruthu {
class IGenerate {
public:
    virtual ~IGenerate() = default;

    virtual std::vector<std::shared_ptr<Cruthu::Point>> Create() = 0;
    virtual std::shared_ptr<Cruthu::Point> GetSignificantPoint() = 0;
};
} // namespace Cruthu
#endif

