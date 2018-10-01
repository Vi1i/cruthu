#ifndef CRUTHU_IGENERATE_HPP
#define CRUTHU_IGENERATE_HPP

#include "Point.hpp"

#include <vector>

namespace Cruthu {
class IGenerate {
public:
    virtual ~IGenerate() = default;

    virtual std::vector<std::shared_ptr<Cruthu::Point>> Create() = 0;
};
} // namespace Cruthu
#endif

