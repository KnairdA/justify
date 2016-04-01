#include "line_accumulator.h"

#include <iostream>
#include <algorithm>

LineAccumulator::LineAccumulator(const std::size_t max_length):
	max_length_{max_length},
	random_{},
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

		const std::size_t missing = this->max_length_ - this->length_;
		const std::size_t base    = missing / (this->tokens_.size()-1);

		std::for_each(
			this->tokens_.begin(),
			this->tokens_.end()-2,
			[base, this](auto& token) {
				token.second  += base;
				this->length_ += base;
			}
		);

		auto range = this->random_.makeRange(0, this->tokens_.size()-2);

		while ( this->length_ < this->max_length_ ) {
			this->tokens_[range.get()].second += 1;
			this->length_                     += 1;
		}
	}

	for ( const auto& token : this->tokens_ ) {
		std::cout << token.first
		          << std::string(token.second, ' ');
	}

	std::cout << '\n';

	this->length_ = 0;
	this->tokens_.clear();
}
