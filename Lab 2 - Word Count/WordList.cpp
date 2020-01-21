// Definitions of WordOccurrence and WordList classes
// CS44001 Assignment 2 - Word Count
// Connor DeGeorge
// 1/27/20

#include "WordList.h"

WordOccurrence::WordOccurrence(const string& word, int num) {
	word_ = word;
	num_ = num;
}

// Checks if two words are the same
bool WordOccurrence::matchWord(const string &word) {
	if (word == word_) return true;
	return false;
}

// Adds one to the number of occurrences
void WordOccurrence::increment() {
	num_++;
}

// Returns the word in the occurrence
string WordOccurrence::getWord() const {
	return word_;
}

// Returns the number in the occurrence
int WordOccurrence::getNum() const {
	return num_;
}

WordList::WordList() {
	size_ = 0;
	wordArray_ = new WordOccurrence[size_];
}

WordList::WordList(const WordList& wordList) {
	size_ = wordList.size_;
	wordArray_ = new WordOccurrence[size_];
	for (int i = 0; i < size_; i++)
		wordArray_[i] = wordList.wordArray_[i];
}

WordList::~WordList() {
	delete[] wordArray_;
}

WordList& WordList::operator=(const WordList& wordList) {
	if (this == &wordList) return *this;

	size_ = wordList.size_;
	wordArray_ = wordList.wordArray_;
	for (int i = 0; i < size_; i++)
		wordArray_[i] = wordList.wordArray_[i];

	return *this;
}

// Inserts the word into the wordlist
void WordList::addWord(const string &word) {
	// If word is already in array, increment number
	for (int i = 0; i < size_; i++) {
		if (wordArray_[i].getWord() == word)
			return wordArray_[i].increment();
	}

	// Increase array size
	WordOccurrence *temp = new WordOccurrence[size_ + 1];
	for (int j = 0; j < size_; j++) {
		temp[j] = wordArray_[j];
	}
	size_++;
	delete[] wordArray_;
	wordArray_ = temp;
	
	wordArray_[size_ - 1] = WordOccurrence(word, 1);
}

// Outputs each word and the number of times it occurs
void WordList::print() {
	// Determine the highest occurrence
	int highest = 0;
	for (int i = 0; i < size_; i++) {
		int numAtIndex = wordArray_[i].getNum();
		if (numAtIndex > highest) highest = numAtIndex;
	}

	// Print title line
	std::cout << "Words in order of occurrence:" << std::endl;

	// Loop through and print word for each occurrence count
	int number = 0;
	while (number <= highest) {
		for (int j = 0; j < size_; j++) {
			int numOfOccurrence = wordArray_[j].getNum();
			if (numOfOccurrence == number)
				std::cout << wordArray_[j].getWord() << ": "<<
				std::to_string(numOfOccurrence) << std::endl;
		}
		number++;
	}
}

// Checks if the two WordLists are equal
bool equal(const WordList& left, const WordList& right) {
	if (left.size_ != right.size_) return false;

	for (int i = 0; i < left.size_; i++) {
		if (left.wordArray_[i].getNum() != right.wordArray_[i].getNum() ||
			left.wordArray_[i].getWord() != right.wordArray_[i].getWord())
			return false;
	}

	return true;
}