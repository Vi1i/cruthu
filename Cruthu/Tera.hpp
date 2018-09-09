#ifndef CRUTHU_TERA_HPP
#define CRUTHU_TERA_HPP

#include "Point.hpp"
#include "IGenerate.hpp"

#include <memory>
#include <vector>

namespace Cruthu {
class Tera {
public:
    Tera(std::shared_ptr<Cruthu::IGenerate> generator);
    ~Tera() = default;
    
    const std::vector<Cruthu::Point> & Points();

private:
    std::vector<Cruthu::Point> mPoints;

};
} // namespace Cruthu
#endif
