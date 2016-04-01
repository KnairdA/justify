#include "line_accumulator.h"

#include <iostream>
#include <algorithm>

namespace {

std::vector<std::uint8_t> getRandomIndizes(
	std::random_device& device,
	const std::uint8_t n) {
	std::vector<std::uint8_t> indizes(n);
	std::iota(indizes.begin(), indizes.end(), 0);
	std::shuffle(
		indizes.begin(),
		indizes.end(),
		std::mt19937{device()}
	);

	return indizes;
}

}

LineAccumulator::LineAccumulator(const std::uint8_t max_length):
	max_length_{max_length},
	device_{},
	length_{0},
	tokens_{} { }

LineAccumulator::~LineAccumulator() {
	this->discharge(false);
}

void LineAccumulator::operator()(const std::string& word) {
	if ( ( this->length_ + word.length() ) > this->max_length_ ) {
		this->discharge(true);
	}

	this->tokens_.emplace_back(word, 0);
	this->length_ += word.length();

	if ( this->length_ < this->max_length_ ) {
		this->tokens_.back().second += 1;
		this->length_               += 1;
	}
}

void LineAccumulator::discharge(const bool full) {
	if ( full ) {
		this->length_              -= this->tokens_.back().second;
		this->tokens_.back().second = 0;

		const std::uint8_t missing = this->max_length_ - this->length_;
		const std::uint8_t base    = missing / (this->tokens_.size()-1);

		std::for_each(
			this->tokens_.begin(),
			this->tokens_.end()-2,
			[base, this](auto& token) {
				token.second  += base;
				this->length_ += base;
			}
		);

		auto indizes = getRandomIndizes(this->device_, this->tokens_.size()-1);

		std::for_each(
			indizes.begin(),
			indizes.begin()+(this->max_length_ - this->length_),
			[this](std::uint8_t x) {
				this->tokens_[x].second += 1;
			}
		);
	}

	for ( const auto& token : this->tokens_ ) {
		std::cout << token.first
		          << std::string(token.second, ' ');
	}

	std::cout << '\n';

	this->length_ = 0;
	this->tokens_.clear();
}
