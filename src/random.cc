#include "random.h"

namespace utility {

std::size_t Random::Range::get() {
	return this->distribution_(*(this->generator_));
}

Random::Range::Range(
	std::mt19937* const generator,
	const std::size_t   a,
	const std::size_t   b
):
	generator_(generator),
	distribution_(a, b) { }

Random::Random():
	device_{},
	generator_{device_()} { }

Random::Range Random::makeRange(
	const std::size_t a,
	const std::size_t b) {
	this->generator_.seed(this->device_());

	return Range{&(this->generator_), a, b};
}

}
