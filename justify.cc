#include <string>
#include <iostream>

#include "line_accumulator.h"

int main(int argc, char* argv[]) {
	std::cout.sync_with_stdio(false);
	std::cin.sync_with_stdio(false);

	std::uint8_t max_line_length = 60;

	if ( argc == 2 ) {
		const int user_length = std::stoi(argv[1]);

		if ( user_length > 1 && user_length < 256 ) {
			max_line_length = user_length;
		} else {
			std::cerr << "Invalid line length.\n";

			return -1;
		}
	}

	justify::LineAccumulator acc{max_line_length};
	std::string              token;

	while ( std::cin >> token ) {
		acc(token);
	}

	return 0;
}
