#pragma once

#include <tuple>
#include <string>
#include <vector>
#include <random>

namespace justify {

class LineAccumulator {
	public:
		LineAccumulator(const std::uint8_t max_length, const std::uint8_t offset);
		~LineAccumulator();

		std::uint8_t getMissing() const;

		void operator()(const std::string& token);

	private:
		const std::uint8_t max_length_;
		const std::uint8_t offset_;

		std::uint8_t length_;

		std::vector<
			std::pair<std::string, std::uint8_t>
		> tokens_;

		void justify();
		void discharge(const bool full);

};

}
