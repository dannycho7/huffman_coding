all: frequencies

frequencies: frequencies.cpp
	g++ ./frequencies.cpp -o ./frequencies.out

clean:
	rm *.out
