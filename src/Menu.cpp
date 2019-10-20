#include "Menu.hpp"
#include <iostream>
#include <limits>

namespace GraphCreator {

	Menu::Menu( const std::string &currentDir, const std::string &filePath )
			: creator( currentDir, filePath ) {}

	void Menu::exec() {
		fillCommands();
		try {
			execTry();
		}
		catch( FileException &e ) {
			exceptionHandler( e );
		}
	}

	void Menu::fillCommands() {
		commands[HELP].name = "help";
		commands[HELP].handler = std::bind( &Menu::outputAllCommandInfos, this );
		commands[HELP].info = ":\t display all commands with information on them.";

		commands[CR_ID].name = "cr id";
		commands[CR_ID].handler = std::bind( &Menu::changeRangeId, this );
		commands[CR_ID].info = ":\t changes the range of displayed node identifiers.";

		commands[CR_COLOR].name = "cr color";
		commands[CR_COLOR].handler = std::bind( &Menu::changeRangeColor, this );
		commands[CR_COLOR].info = ":\t changes the range of displayed node colors.";

		commands[CR_WEIGHT].name = "cr weight";
		commands[CR_WEIGHT].handler = std::bind( &Menu::changeRangeWeight, this );
		commands[CR_WEIGHT].info = ":\t changes the range of displayed edge weights.";

		commands[CONVERT].name = "convert";
		commands[CONVERT].handler = std::bind( &Menu::convert, this );
		commands[CONVERT].info = ":\t converts input file to graph.";

		commands[SHOW].name = "show";
		commands[SHOW].handler = std::bind( &Menu::showGraph, this );
		commands[SHOW].info = ":\t displays graph in browser by default.";

		commands[EXIT].name = "exit";
		commands[EXIT].handler = []{};
		commands[EXIT].info = ":\t exit from the program.";
	}

	void Menu::exceptionHandler( const std::exception &e ) const {
		std::cout << "\nERROR: " << e.what() << std::endl;
		exit( 1 );
	}

	void Menu::execTry() {
		outputInfo();
		while ( menuSelector() ) {}
	}

	bool Menu::menuSelector() {
		const auto command = takeNextCommand();
		if ( commands.at( EXIT ).name == command ) {
			return false;
		}
		execCommand( command );

		return true;
	}

	std::string Menu::takeNextCommand() const {
		std::string command;
		std::cout << "Enter command: ";
		std::getline( std::cin, command );
		return command;
	}

	void Menu::execCommand( const std::string &inputCommand ) const {
		bool isCommandCorrect = false;
		for ( const auto &command : commands ) {
			if ( command.name == inputCommand ) {
				isCommandCorrect= true;
				command.handler();
				break;
			}
		}
		if ( !isCommandCorrect ) {
			std::cout << "The following command is incorrect \"" << inputCommand << "\". Try the help command.\n";
		}
	}

	void Menu::outputInfo() const {
		auto converter = creator.takeConverter();

		const auto vNum = converter->getVNum();
		const auto eNum = converter->getENum();
		std::cout << "Num of vertices: " << vNum << "\tNum of edges: " << eNum << "\n";
	}

	void Menu::outputAllCommandInfos() const {
		for ( int i = FIRST_COMMAND_NUM; i <= LAST_COMMAND_ID; ++i ) {
			std::cout << "\t" << commands.at( i ).name << commands.at( i ).info << "\n";
		}
	}

	void Menu::changeRangeId() const {
		std::cout << "changeRangeId\n";
	}

	void Menu::changeRangeColor() const {
		std::cout << "changeRangeColor\n";

	}

	void Menu::changeRangeWeight() const {
		std::cout << "changeRangeWeight\n";

	}

	void Menu::convert() {
		std::cout << "convert\n";
		creator.convertToGraph();
	}

	void Menu::showGraph() const {
		std::string command = ( "sensible-browser " );

		auto graphPath = creator.getGraphPath();

		command.append( graphPath );

		system( command.c_str() );
	}

}
