all: frequencies huffman

frequencies: frequencies.cpp
	g++ ./frequencies.cpp -o ./frequencies.out

huffman: huffman.cpp
	g++ ./huffman.cpp -o ./huffman.out

clean:
	rm *.out
