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
	int char_code = 0, bitsRead = 8; // set bitsRead to 8 so we can start with a read
	bool done = false;

	while (1) {
		while (huffman_code_to_char_code.find(code) == huffman_code_to_char_code.end()) {
			if (bitsRead == 8) {
				if ((c = getchar()) == EOF) {
					done = true;
					break;
				}
				char_code = (int) c;
				bitsRead = 0;
			}

			int mask = (1 << (7 - bitsRead));
			if ((char_code & mask) == 0) {
				code += "0";
			} else {
				code += "1";
			}
			bitsRead++;
		}

		if (done) break;
		std::cout << (char) huffman_code_to_char_code[code];
		code = "";
	}

	return 0;
}