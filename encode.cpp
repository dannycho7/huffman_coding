#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include "huffman_code_mapping.h"

int main(int argc, char* argv[]) {
	std::vector<char> outputBuf;
	char c;

	if (argc != 2) {
		std::cerr << "Correct Usage: ./encode.out <codewords_filepath>" << std::endl;
		throw;
	}

	std::unordered_map<int, std::string> huffman_codes;
	generate_huffman_code_mapping(huffman_codes, argv[1]);

	const int bufSize = 8;
	int numBytesWriteBuf = 0, writeBuf = 0;

	while (feof(stdin) == 0) {
		int char_code = (int) getchar();
		std::string code = huffman_codes[char_code];

		for (int i = 0; i < code.length(); i++) {
			writeBuf <<= 1;
			numBytesWriteBuf++;
			if (code[i] == '1') 
				writeBuf++;

			if (numBytesWriteBuf == bufSize) {
				outputBuf.push_back((char) writeBuf);
				writeBuf = 0;
				numBytesWriteBuf = 0;
			}
		}
	}

	const int numBits = outputBuf.size() * 8 + numBytesWriteBuf;
	std::cout << numBits;

	if (numBytesWriteBuf != 0) {
		writeBuf <<= bufSize - numBytesWriteBuf;
		outputBuf.push_back((char) writeBuf);
		writeBuf = 0;
		numBytesWriteBuf = 0;
	}

	for (int i = 0; i < outputBuf.size(); i++) {
		std::cout << outputBuf[i];
	}

	return 0;
}