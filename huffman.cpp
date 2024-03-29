#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include "node.h"

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

	while (!nodes.empty() && nodes.size() > 1) {
		Node* one = new Node(nodes.top());
		nodes.pop();
		Node* two = new Node(nodes.top());
		nodes.pop();

		Node x(-1, one->freq + two->freq, one, two);
		nodes.push(x);
	}

	Node* huffman_head = new Node(nodes.top());
	nodes.pop();

	std::cout << dumpHuffmanTree(huffman_head) << std::endl;
	huffman_head->delete_all();

	return 0;
}