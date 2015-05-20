
all: endoh1cpp endoh1.js

endoh1cpp:
	g++ -O3 -std=c++11 endoh1.cpp -o endoh1cpp

endoh1.js:
	tsc endoh1.ts
