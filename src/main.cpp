#include <iostream>
#include "GraphCreator.hpp"

int main( int argc, char *argv[] ) {
	
	if ( 2 != argc ) {
		exit( -1 );
	}
	
	auto creator = GraphCreator::createCreator();
	const auto dirPathIndex = 0;
	const auto filePathIndex = 1;
	const std::string currentDir( argv[dirPathIndex] );
	const std::string filePath( argv[filePathIndex] );
	creator->exec( currentDir, filePath );
	
	return 0;
}
