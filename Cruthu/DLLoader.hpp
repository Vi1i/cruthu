#include "IDLLoader.hpp"

#include <dlfcn.h>

#include <iostream>

namespace Cruthu {
template <class T>
class DLLoader : public IDLLoader<T> {
public:
    DLLoader(std::string const &pathToLib,
            std::string const &allocClassSymbol = "allocator",
            std::string const &deleteClassSymbol = "deleter") :
        mHandle(nullptr), mPathToLib(pathToLib),
        mAllocClassSymbol(allocClassSymbol), mDeleteClassSymbol(deleteClassSymbol) {}

    ~DLLoader() = default;

    void DLOpenLib() override {
        if (!(this->mHandle = dlopen(this->mPathToLib.c_str(), RTLD_NOW | RTLD_LAZY))) {
            std::cerr << dlerror() << std::endl;
        }
    }

    void DLCloseLib() override {
        if (dlclose(this->mHandle) != 0) {
            std::cerr << dlerror() << std::endl;
        }
    }

    std::shared_ptr<T> DLGetInstance() override {
        using allocClass = T *(*)();
        using deleteClass = void (*)(T *);

        auto allocFunc = reinterpret_cast<allocClass>(dlsym(this->mHandle, this->mAllocClassSymbol.c_str()));
        auto deleteFunc = reinterpret_cast<deleteClass>(dlsym(this->mHandle, this->mDeleteClassSymbol.c_str()));

        if (!allocFunc || !deleteFunc) {
            this->DLCloseLib();
            std::cerr << dlerror() << std::endl;
        }

        return std::shared_ptr<T>(allocFunc(), [deleteFunc](T *p){ deleteFunc(p); });
    }

private:
    void * mHandle;
    std::string	mPathToLib;
    std::string	mAllocClassSymbol;
    std::string	mDeleteClassSymbol;
};
}
