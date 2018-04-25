#include <cstdio>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>

int main() {
	char c;
	std::map<int, int> freq;

	while ((c = getchar()) != EOF) {
		int char_code = c;
		freq[char_code]++;
	}

	for (std::map<int, int>::iterator it = freq.begin(); it != freq.end(); it++) {
		std::cout << std::setw(8) << std::left << it->first << it->second << std::endl;
	}

	return 0;
}
