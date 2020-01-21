// Header file that contains class definations of WordOccurrence and WordList
// CS44001 Assignment 2 - Word Count
// Connor DeGeorge
// 1/27/20

#ifndef WORDLIST_H
#define WORDLIST_H

#include <iostream>
#include <string>

using std::string;

class WordOccurrence {
public:
	WordOccurrence(const string& word = "", int num = 0);
	bool matchWord(const string &); // returns true if word matches stored
	void increment(); // increments number of occurrences
	string getWord() const;
	int getNum() const;

private:
	string word_;
	int num_;
};

class WordList {
public:
	WordList();
	WordList(const WordList&);
	~WordList();
	WordList& operator=(const WordList&);

	// implement comparison as friend
	friend bool equal(const WordList&, const WordList&);

	void addWord(const string &);
	void print();
private:
	WordOccurrence *wordArray_; // a dynamically allocated array of WordOccurrences
								// may or may not be sorted
	int size_;
};

#endif // !WORDLIST_H