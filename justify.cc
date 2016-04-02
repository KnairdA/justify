#include <iostream>

#include "line_accumulator.h"

int main() {
	std::cout.sync_with_stdio(false);
	std::cin.sync_with_stdio(false);

	justify::LineAccumulator acc{60};
	std::string              token;

	while ( std::cin >> token ) {
		acc(token);
	}
}
