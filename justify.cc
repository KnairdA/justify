#include <iostream>

#include "line_accumulator.h"

int main() {
	std::cout.sync_with_stdio(false);
	std::cin.sync_with_stdio(false);

	LineAccumulator acc{60};
	std::string     word;

	while ( std::cin >> word ) {
		acc(word);
	}
}
