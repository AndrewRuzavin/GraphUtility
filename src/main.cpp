#include <iostream>
#include "Menu.hpp"

int main( int argc, char *argv[] ) {
	
	if ( 2 != argc ) {
		std::cout << "ERROR: Invalid number of arguments.\n";
		exit( -1 );
	}
	
	const auto dirPathIndex = 0;
	const auto filePathIndex = 1;
	const std::string currentDir( argv[dirPathIndex] );
	const std::string filePath( argv[filePathIndex] );

	GraphCreator::Menu menu( currentDir, filePath );
	menu.exec();
	
	return 0;
}
