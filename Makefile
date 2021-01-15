build:
	g++ -O2 -o run -std=c++17 main.cpp controller/*.cpp writer/*.cpp reader/*.cpp -o o_ran -lpthread -lhiredis
