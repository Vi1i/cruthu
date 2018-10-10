#ifndef CRUTHU_IDLLOADER_HPP
#define CRUTHU_IDLLOADER_HPP

#include <memory>
#include <string>

namespace cruthu {
template <class T>
class IDLLoader {
public:
    virtual ~IDLLoader() = default;

    virtual void DLOpenLib() = 0;
    virtual std::shared_ptr<T> DLGetInstance() = 0;
    virtual void DLCloseLib() = 0;
};
}
#endif
