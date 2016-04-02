#include "line_accumulator.h"

#include <cassert>
#include <iostream>
#include <algorithm>

namespace {

std::uint8_t getRandomIndex(
	std::mt19937&      random,
	const std::uint8_t n
) {
	return std::uniform_int_distribution<std::uint8_t>{0, n}(random);
}

std::vector<std::uint8_t> getRandomIndizes(
	std::mt19937&      random,
	const std::uint8_t n
) {
	std::vector<std::uint8_t> indizes(n);
	std::iota(indizes.begin(), indizes.end(), 0);
	std::shuffle(
		indizes.begin(),
		indizes.end(),
		random
	);

	return indizes;
}

}

LineAccumulator::LineAccumulator(const std::uint8_t max_length):
	max_length_{max_length},
	device_{},
	random_{device_()},
	length_{0},
	tokens_{} { }

LineAccumulator::~LineAccumulator() {
	this->discharge(false);
}

std::uint8_t LineAccumulator::getMissing() const {
	return this->max_length_ - this->length_;
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

void LineAccumulator::justify() {
	switch ( this->tokens_.size() ) {
		// There is no sensible block justification of null or any single token
		case 0:
		case 1: {
			this->length_ = this->max_length_;

			break;
		}
		// i.e. left align the first token and right align the second token
		case 2: {
			this->tokens_[0].second += this->getMissing();
			this->length_            = this->max_length_;

			break;
		}
		// most common branch for normal texts, add the maximum equal amount of
		// spaces to all but the last token
		default: {
			const std::uint8_t base = this->getMissing()
			                        / (this->tokens_.size() - 2);

			std::for_each(
				this->tokens_.begin(),
				this->tokens_.end() - 2,
				[&, base](auto& token) {
					token.second  += base;
					this->length_ += base;
				}
			);

			break;
		}
	}

	assert(this->getMissing() < this->tokens_.size());

	switch ( this->getMissing() ) {
		case 0: {
			break;
		}
		// randomly distribute missing spaces
		case 1: {
			this->tokens_[
				getRandomIndex(this->random_, this->tokens_.size() - 2)
			].second += 1;

			break;
		}
		default: {
			const auto indizes = getRandomIndizes(
				this->random_,
				this->tokens_.size() - 2
			);

			std::for_each(
				indizes.begin(),
				indizes.begin() + this->getMissing(),
				[&](std::uint8_t x) {
					this->tokens_[x].second += 1;
					this->length_           += 1;
				}
			);

			break;
		}
	}
}

void LineAccumulator::discharge(const bool full) {
	this->length_              -= this->tokens_.back().second;
	this->tokens_.back().second = 0;

	if ( full ) {
		this->justify();
	}

	for ( const auto& token : this->tokens_ ) {
		std::cout << token.first
		          << std::string(token.second, ' ');
	}

	std::cout << '\n';

	this->length_ = 0;
	this->tokens_.clear();
}
