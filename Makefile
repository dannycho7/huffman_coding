all: frequencies huffman encode decode

encode: encode.cpp
	g++ -std=c++11 ./encode.cpp -o ./encode.out

decode: decode.cpp
	g++ -std=c++11 ./decode.cpp -o ./decode.out

frequencies: frequencies.cpp
	g++ ./frequencies.cpp -o ./frequencies.out

huffman: huffman.cpp
	g++ ./huffman.cpp -o ./huffman.out

clean:
	rm *.out
