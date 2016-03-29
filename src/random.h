#pragma once

#include <random>

namespace utility {

class Random {
	public:
		class Range {
			public:
				std::size_t get();

			protected:
				friend class Random;

				Range(std::mt19937* const, const std::size_t, const std::size_t);

			private:
				std::mt19937* const                        generator_;
				std::uniform_int_distribution<std::size_t> distribution_;
		};

		Random();

		Range makeRange(const std::size_t, const std::size_t);

	private:
		std::random_device device_;
		std::mt19937       generator_;

};


}
