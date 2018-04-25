#ifndef NODE_H
#define NODE_H

#include <iostream>

struct Node {
	Node(const Node& copy) {
		this->char_code = copy.char_code;
		this->freq = copy.freq;
		this->left = copy.left;
		this->right = copy.right;
	}

	Node(int char_code, int freq = -1, Node* left = NULL, Node* right = NULL) {
		if (freq == 0) {
			std::cerr << "Frequency can't be zero" << std::endl;
			throw;
		}

		this->char_code = char_code;
		this->freq = freq;
		this->left = left;
		this->right = right;
	};

	void delete_all() {
		if (this->right != NULL) 
			this->right->delete_all();
		if (this->left != NULL)
			this->left->delete_all();
		delete this;
	}

	bool operator >(const Node& y) const {
		return this->freq > y.freq;
	}

	int char_code;
	int freq;
	Node* left;
	Node* right;
};

#endif
