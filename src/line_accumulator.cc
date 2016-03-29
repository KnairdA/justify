#include "line_accumulator.h"

#include <iostream>

LineAccumulator::LineAccumulator(const std::size_t max_length):
	max_length_{max_length},
	random_{},
	length_{0},
	tokens_{},
	spaces_{} { }

LineAccumulator::~LineAccumulator() {
	this->discharge(false);
}

void LineAccumulator::operator()(const std::string& word) {
	if ( ( this->length_ + word.length() + 1 ) > this->max_length_ ) {
		this->pop_trailing_token();
		this->discharge(true);
	}

	this->add_token(word);
	this->add_space();
}

void LineAccumulator::add_token(const std::string& token) {
	this->length_ += token.length();
	this->tokens_.emplace_back(token);
}

void LineAccumulator::add_space() {
	this->add_token(" ");
	this->spaces_.emplace_back(this->tokens_.size() - 1);
}

void LineAccumulator::increase_space_at(const std::size_t index) {
	this->tokens_.at(this->spaces_[index]).append(" ");
	++this->length_;
}

void LineAccumulator::pop_trailing_token() {
	this->length_ -= this->tokens_.back().length();
	this->tokens_.pop_back();
	this->spaces_.pop_back();
}

void LineAccumulator::discharge(const bool full) {
	if ( full ) {
		auto range = this->random_.makeRange(0, this->spaces_.size()-1);

		while ( this->length_ < this->max_length_ ) {
			this->increase_space_at(range.get());
		}
	}

	for ( const auto& token : this->tokens_ ) {
		std::cout << token;
	}

	std::cout << '\n';

	this->length_ = 0;
	this->tokens_.clear();
	this->spaces_.clear();
}
