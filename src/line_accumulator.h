#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <random>

namespace justify {

class LineAccumulator {
	public:
		LineAccumulator(const std::uint8_t max_length);
		~LineAccumulator();

		std::uint8_t getMissing() const;

		void operator()(const std::string& token);

	private:
		const std::uint8_t max_length_;

		std::random_device device_;
		std::mt19937       random_;
		std::uint8_t       length_;

		std::vector<
			std::pair<std::string, std::uint8_t>
		> tokens_;

		void justify();
		void discharge(const bool full);

};

}
