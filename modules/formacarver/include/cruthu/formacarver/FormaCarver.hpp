#ifndef CRUTHU_FORMACARVER_HPP
#define CRUTHU_FORMACARVER_HPP

#include <cruthu/IForma.hpp>

namespace cruthu {
class FormaCarver : public IForma {
    FormaCarver() = default;
    ~FormaCarver() = default;
};
}

extern "C" {
	cruthu::FormaCarver * allocator() {
		return new cruthu::FormaCarver();
	}

	void deleter(cruthu::FormaCarver * ptr) {
		delete ptr;
	}
}
} // namespace cruthu
#endif
