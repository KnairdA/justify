#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <random>

class LineAccumulator {
	public:
		LineAccumulator(const std::uint8_t max_length);
		~LineAccumulator();

		void operator()(const std::string& word);

	private:
		const std::uint8_t max_length_;

		std::random_device device_;
		std::uint8_t       length_;

		std::vector<
			std::pair<std::string, std::uint8_t>
		> tokens_;

		void discharge(const bool full);

};

