all: frequencies huffman encode decode

encode: encode.cpp
	g++ -std=c++11 ./encode.cpp -o ./encode

decode: decode.cpp
	g++ -std=c++11 ./decode.cpp -o ./decode

frequencies: frequencies.cpp
	g++ ./frequencies.cpp -o ./frequencies

huffman: huffman.cpp
	g++ ./huffman.cpp -o ./huffman

clean:
	rm -f encode decode frequencies huffman
