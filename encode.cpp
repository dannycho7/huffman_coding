#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

void generate_huffman_code_mapping(std::unordered_map<int, std::string>& huffman_codes, char* codewords_filepath) {
	std::fstream file(codewords_filepath);
	std::string linebuf;
	while (std::getline(file, linebuf)) {
		int char_code;
		std::string huffman_code;
		std::stringstream in(linebuf);
		in >> char_code >> huffman_code;
		huffman_codes[char_code] = huffman_code;
	}
	file.close();
};

int main(int argc, char* argv[]) {
	char c;

	if (argc != 2) {
		std::cerr << "Correct Usage: ./encode.out <codewords_filepath>" << std::endl;
		throw;
	}

	std::unordered_map<int, std::string> huffman_codes;
	generate_huffman_code_mapping(huffman_codes, argv[1]);

	const int bufSize = 8;
	int numBytesWriteBuf = 0, writeBuf = 0;

	while ((c = getchar()) != EOF) {
		int char_code = (int) c;
		std::string code = huffman_codes[char_code];

		for (int i = 0; i < code.length(); i++) {
			writeBuf <<= 1;
			numBytesWriteBuf++;
			if (code[i] == '1') 
				writeBuf++;

			if (numBytesWriteBuf == bufSize) {
				std::cout << std::bitset<bufSize>(writeBuf);
				writeBuf = 0;
				numBytesWriteBuf = 0;
			}
		}
	}

	if (numBytesWriteBuf != 0) {
		writeBuf <<= bufSize - numBytesWriteBuf;
		std::cout << std::bitset<bufSize>(writeBuf);
		writeBuf = 0;
		numBytesWriteBuf = 0;
	}

	return 0;
}