#pragma once

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

		utility::Random          random_;
		std::size_t              length_;
		std::vector<std::string> tokens_;
		std::vector<std::size_t> spaces_;

		void add_token(const std::string& token);
		void add_space();

		void increase_space_at(const std::size_t index);
		void pop_trailing_token();

		void discharge(const bool full);

};

