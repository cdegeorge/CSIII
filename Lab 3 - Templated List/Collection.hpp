// Header file that contains class definations of Collection
// CS44001 Assignment 3 - Templated List
// Connor DeGeorge
// 2/3/20

#ifndef COLLECTION_HPP
#define COLLECTION_HPP

#include <iostream>
#include "list.hpp"

template <typename T>
class Collection {
public:
	Collection() : front_(nullptr) {}

	void addItem(const T &item);
	void removeItem(const T& item);
	void printCollection();
	T lastItem() const { return front_->getData(); } // Returns the last item added to the collection

	template <typename U>
	friend bool equal(const Collection<U>&, const Collection<U>&);
private:
	node<T>* front_;
};

// Takes an item as the argument and adds it to the collection
template <typename T>
void Collection<T>::addItem(const T& item) {
	node<T>* newNode = new node<T>;
	newNode->setData(item);
	newNode->setNext(front_);
	front_ = newNode;
}

// Takes an item as the argument and removes all instances of this item from the collection
template <typename T>
void Collection<T>::removeItem(const T& item) {
	node<T>* previousNode = nullptr;
	node<T>* currentNode = front_;
	node<T>* nextNode;

	while (currentNode != nullptr) {
		nextNode = currentNode->getNext();
		if (currentNode->getData() == item) {
			if (previousNode != nullptr) // Move the previous node forward to fill empty space
				previousNode->setNext(currentNode->getNext());
			delete currentNode;
		}
		if (currentNode != nullptr)
			previousNode = currentNode;
		currentNode = nextNode;
	}
}

// Prints all items in the collection
template <typename T>
void Collection<T>::printCollection() {
	node<T>* currentNode = front_;

	while (currentNode != nullptr) {
		std::cout << currentNode->getData() << ' ';
		currentNode = currentNode->getNext();
	}
	std::cout << std::endl;
}

template <typename U>
bool equal(const Collection<U>& lhs, const Collection<U>& rhs) {
	node<U>* left = lhs.front_;
	node<U>* right = rhs.front_;

	// Compare each element
	while (left != nullptr && right != nullptr) {
		if (left->getData() != right->getData())
			return false;
		left = left->getNext();
		right = right->getNext();
	}

	// Check if any are nullptrs
	if ((left == nullptr && right != nullptr) ||
		(left != nullptr && right == nullptr))
		return false;

	return true;
}

#endif // !COLLECTION_HPP
