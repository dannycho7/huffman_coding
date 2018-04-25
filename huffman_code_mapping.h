#include <fstream>
#include <sstream>
#include <string>
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

void generate_inverted_huffman_code_mapping(std::unordered_map<std::string, int>& huffman_codes, char* codewords_filepath) {
	std::fstream file(codewords_filepath);
	std::string linebuf;
	while (std::getline(file, linebuf)) {
		int char_code;
		std::string huffman_code;
		std::stringstream in(linebuf);
		in >> char_code >> huffman_code;
		huffman_codes[huffman_code] = char_code;
	}
	file.close();
};