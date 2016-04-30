#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <random>

namespace justify {

class LineAccumulator {
	public:
		LineAccumulator(
			const std::uint8_t  max_length,
			const std::uint8_t  offset,
			const std::uint32_t seed
		);
		~LineAccumulator();

		void operator()(const std::string& token);

	private:
		const std::uint8_t max_length_;
		const std::uint8_t offset_;

		std::mt19937 generator_;
		std::uint8_t length_;

		std::vector<
			std::pair<std::string, std::uint8_t>
		> tokens_;

		std::uint8_t getMissing() const;

		void justify();
		void discharge(const bool full);

};

}
