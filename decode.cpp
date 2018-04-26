#include <cstdio>
#include <iostream>
#include <string>
#include "huffman_code_mapping.h"

int main(int argc, char* argv[]) {
	char c;

	if (argc != 2) {
		std::cerr << "Correct Usage: ./decode.out <codewords_filepath>" << std::endl;
		throw;
	}

	std::unordered_map<std::string, int> huffman_code_to_char_code;
	generate_inverted_huffman_code_mapping(huffman_code_to_char_code, argv[1]);

	std::string code = "";
	int char_code = 0, bitsReadFromBuf = 0, bitsReadTotal = 0, numBitsInput;
	bool done = false;

	std::cin >> numBitsInput;

	while (1) {
		if (bitsReadTotal == numBitsInput) break;

		while (huffman_code_to_char_code.find(code) == huffman_code_to_char_code.end()) {
			if (bitsReadFromBuf == 8 || bitsReadTotal == 0) {
				char_code = (int) getchar();
				bitsReadFromBuf = 0;
				
				if (feof(stdin) != 0) {
					std::cout << (int) c << std::endl;
					done = true;
					break;
				}				
			}

			int mask = (1 << (7 - bitsReadFromBuf));
			if ((char_code & mask) == 0) {
				code += "0";
			} else {
				code += "1";
			}
			bitsReadFromBuf++;
			bitsReadTotal++;
		}

		if (done) break;
		std::cout << (char) huffman_code_to_char_code[code];
		code = "";
	}

	return 0;
}