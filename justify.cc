#include <string>
#include <iostream>

#include <boost/optional.hpp>
#include <boost/program_options.hpp>

#include "line_accumulator.h"

boost::optional<boost::program_options::variables_map> input(
	int argc, char* argv[]) {
	boost::program_options::options_description optionDescription(
		"Supported options"
	);

	optionDescription.add_options()
		(
			"length",
			boost::program_options::value<int>(),
			"Output line length"
		)
		(
			"offset",
			boost::program_options::value<int>(),
			"Number of spaces to be prepended on each line"
		)
		(
			"seed",
			boost::program_options::value<std::uint32_t>(),
			"Seed for pseudorandomly distributing missing spaces"
		)
	;

	boost::program_options::variables_map variables;

	try {
		boost::program_options::store(
			boost::program_options::parse_command_line(
				argc, argv, optionDescription
			),
			variables
		);

		boost::program_options::notify(variables);
	}
	catch ( const std::exception& exception ) {
		std::cerr << exception.what()  << std::endl;
		std::cout << optionDescription << std::endl;

		return boost::optional<boost::program_options::variables_map>();
	}

	return boost::make_optional(variables);
}

bool process(const boost::program_options::variables_map& variables) {
	std::cout.sync_with_stdio(false);
	std::cin.sync_with_stdio(false);

	std::uint8_t  line_length = 60;
	std::uint8_t  line_offset = 0;
	std::uint32_t seed        = 3473018784;

	if ( variables.count("length") ) {
		const int user_length = variables["length"].as<int>();

		if ( user_length > 1 && user_length < 256 ) {
			line_length = user_length;
		} else {
			std::cerr << "Invalid line length.\n";

			return false;
		}
	}

	if ( variables.count("offset") ) {
		const int user_offset = variables["offset"].as<int>();

		if ( user_offset >= 0 && user_offset < 256 ) {
			line_offset = user_offset;
		} else {
			std::cerr << "Invalid line offset.\n";

			return false;
		}
	}

	if ( variables.count("seed") ) {
		seed = variables["seed"].as<std::uint32_t>();
	}

	justify::LineAccumulator acc{line_length, line_offset, seed};
	std::string              token;

	while ( std::cin.good() ) {
		if ( std::cin >> token ) {
			acc(token);
		} else {
			return true;
		}
	}

	return true;
}

int main(int argc, char* argv[]) {
	if ( auto variables = input(argc, argv) ) {
		if ( process(*variables) ) {
			return 0;
		} else {
			return 1;
		}
	} else {
		return 1;
	}
}
