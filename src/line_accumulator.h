#pragma once

#include <tuple>
#include <string>
#include <vector>

#include "random.h"

class LineAccumulator {
	public:
		LineAccumulator(const std::size_t max_length);
		~LineAccumulator();

		void operator()(const std::string& word);

	private:
		const std::size_t max_length_;

		utility::Random random_;
		std::size_t     length_;

		std::vector<
			std::pair<std::string, std::uint8_t>
		> tokens_;

		void discharge(const bool full);

};

