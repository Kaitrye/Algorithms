#include <fstream>
#include <iostream>
#include "Graph.hpp"

int main(int argc, char* argv[]){
	
	Graph G;
	G.load (argv[1]);
	std::cout << G.MST () << std::endl;

	return 0;
}
