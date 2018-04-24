#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Node {
	Node(const Node& copy) {
		this->char_code = copy.char_code;
		this->freq = copy.freq;
		this->left = copy.left;
		this->right = copy.right;
	}

	Node(int char_code, int freq, Node* left = NULL, Node* right = NULL) {
		if (freq == 0) {
			std::cerr << "Frequency can't be zero" << std::endl;
			throw;
		}

		this->char_code = char_code;
		this->freq = freq;
		this->left = left;
		this->right = right;
	};

	bool operator >(const Node& y) const {
		return this->freq > y.freq;
	}

	int char_code;
	int freq;
	Node* left;
	Node* right;
};

int traverseWrite(std::ofstream& outStream, Node* x, std::string code) {
	int bytesWritten = 0;
	if (x == NULL) return bytesWritten;
	if (x->left == NULL && x->right == NULL) {
		outStream << std::setw(6) << std::left << x->char_code << code << std::endl;
		bytesWritten += x->freq * code.length();
	} else {
		bytesWritten += traverseWrite(outStream, x->left, code + "0") + traverseWrite(outStream, x->right, code + "1");
	}

	return bytesWritten;
}

int dumpHuffmanTree(Node* head) {
	int totalBytes = 0;
	std::ofstream codewordsFile("codewords.txt");
	if (head->left == NULL && head->right == NULL) {
		totalBytes += traverseWrite(codewordsFile, head, "0"); // special case: if there is only one character just encode that with 0
	} else {
		totalBytes += traverseWrite(codewordsFile, head, "");
	}
	codewordsFile.close();

	return totalBytes;
}

int main() {
	int char_code, freq;
	std::priority_queue<Node, std::vector<Node>, std::greater<Node> > nodes;

	while (std::cin >> char_code >> freq) {
		Node x(char_code, freq);
		nodes.push(x);
	}

	if (nodes.size() == 0) {
		std::cerr << "There are no characters to encode" << std::endl;
		throw;
	}

	int inc = 10000;

	while (!nodes.empty() && nodes.size() > 1) {
		Node* one = new Node(nodes.top());
		nodes.pop();
		Node* two = new Node(nodes.top());
		nodes.pop();

		Node x(++inc, one->freq + two->freq, one, two);
		nodes.push(x);
	}

	Node huffman_head = nodes.top();
	nodes.pop();

	Node *x = &huffman_head;

	std::cout << dumpHuffmanTree(&huffman_head) << std::endl;
	return 1;
}