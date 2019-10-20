#include "Menu.hpp"
#include <iostream>

namespace GraphCreator {

	Menu::Menu( const std::string &currentDir, const std::string &filePath )
			: creator( currentDir, filePath ) {}

	void Menu::exec() {
		try {
			execTry();
		}
		catch( FileException &e ) {
			exceptionHandler( e );
		}
	}

	void Menu::exceptionHandler( const std::exception &e ) const {
		std::cout << "\nERROR: " << e.what() << std::endl;
		exit( 1 );
	}

	void Menu::execTry() {

		outputInfo();
		while ( true ) {

			creator.convertToGraph();
			showGraph();
			break;
		}
	}

	void Menu::outputInfo() const {
		auto converter = creator.takeConverter();

		const auto vNum = converter->getVNum();
		const auto eNum = converter->getENum();
		std::cout << "Num of vertices: " << vNum << "\tNum of edges: " << eNum << "\n";
	}

	void Menu::showGraph() const {
		std::string command = ( "sensible-browser " );

		auto graphPath = creator.getGraphPath();

		command.append( graphPath );

		system( command.c_str() );
	}

}
