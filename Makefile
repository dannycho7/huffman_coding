all: frequencies huffman encode

encode: encode.cpp
	g++ -std=c++11 ./encode.cpp -o ./encode.out

frequencies: frequencies.cpp
	g++ ./frequencies.cpp -o ./frequencies.out

huffman: huffman.cpp
	g++ ./huffman.cpp -o ./huffman.out

clean:
	rm *.out
