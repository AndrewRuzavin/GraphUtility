#include "Menu.hpp"
#include <iostream>
#include <limits>
#include <regex>

namespace GraphCreator {

	const int Menu::COLOR_MAX_RANGE = 255;

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

		commands[SHOW_SETT].name = "sset";
		commands[SHOW_SETT].handler = std::bind( &Menu::showSettings, this );
		commands[SHOW_SETT].info = ":\t show graph settings.";

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
		fillInfoFields();
		outputInfo();
		while ( menuSelector() ) {}
	}

	void Menu::fillInfoFields() {
		auto converter = creator.takeConverter();

		vNum = converter->getVNum();
		eNum = converter->getENum();

		graphSettings.vertexIdBorder.second = vNum;
		graphSettings.vertexColorBorder.second = COLOR_MAX_RANGE;
		graphSettings.edgeWeightBorder.first = -std::numeric_limits<double>::max();
		graphSettings.edgeWeightBorder.second = std::numeric_limits<double>::max();
	}

	void Menu::outputInfo() const {
		std::cout << "Num of vertices: " << vNum << "\tNum of edges: " << eNum << "\n";
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

	void Menu::outputAllCommandInfos() const {
		for ( int i = FIRST_COMMAND_NUM; i <= LAST_COMMAND_ID; ++i ) {
			std::cout << "\t" << commands.at( i ).name << commands.at( i ).info << "\n";
		}
	}

	void Menu::changeRangeId() {
		size_t lower = 0;
		takeRange( graphSettings.vertexIdBorder
				   , lower
				   , vNum );
	}

	template<class Range, class BorderType>
		void Menu::takeRange( Range &range, const BorderType lower, const BorderType upper ) {
			Range bufRange;
			std::string infoStr( "Enter the range of values with allowable range " + std::to_string( lower )
								 + " - " + std::to_string( upper ) + ":\nEnter lower value: " );

			if ( !takeOneOfRange( bufRange.first, lower, upper, infoStr ) ) {
				return;
			}
			infoStr = "Enter upper value: ";
			if ( !takeOneOfRange( bufRange.second, lower, upper, infoStr ) ) {
				return;
			}

			if ( bufRange.first > bufRange.second ) {
				std::swap( bufRange.first, bufRange.second );
			}

			std::swap( range, bufRange );
			std::cout << "Your new range: " << range.first << " - " << range.second << "\n";
		}

	template<class ValType, class BorderType>
		bool Menu::takeOneOfRange( ValType &val, const BorderType lower, const BorderType upper, const std::string &infoStr ) const {
			std::cout << infoStr;
			auto success = takeValue( val, lower, upper );
			if ( !success ) {
				std::cout << "Wrong value!\n";
				return false;
			}
			return true;
		}

	template<class ValType, class BorderType>
		bool Menu::takeValue( ValType &val, const BorderType lower, const BorderType upper ) const {
			std::string inputStr;
			std::getline( std::cin, inputStr );

			if ( isItNum<ValType>( inputStr ) ) {
				auto res = convertStrToVal<ValType>( inputStr );
				if ( withinTheBorder( res, lower, upper ) ) {
					val = res;
				} else {
					return false;
				}
			} else {
				return false;
			}
			return true;
		}

	template<class ValType>
		bool Menu::isItNum( const std::string &str ) const {
			char *p;
			strtol( str.c_str(), &p, 21 );
			return *p ? false : true;
		}

	template<>
		bool Menu::isItNum<double>( const std::string &str ) const {
			char *p;
			strtod( str.c_str(), &p );
			return *p ? false : true;
		}

	template<class ValType>
		auto Menu::convertStrToVal( const std::string &str ) const {
			return atoi( str.c_str() );
		}

	template<>
		auto Menu::convertStrToVal<double>( const std::string &str ) const {
			return atof( str.c_str() );
		}

	template<class ValType, class BorderType>
		bool Menu::withinTheBorder( const ValType val, const BorderType lower, const BorderType upper ) const {
			return lower <= val
					&& val <= upper;
		}

	void Menu::changeRangeColor() {
		takeRange( graphSettings.vertexColorBorder
				   , 0
				   , COLOR_MAX_RANGE );
	}

	void Menu::changeRangeWeight() {
		takeRange( graphSettings.edgeWeightBorder
				   , -std::numeric_limits<double>::max()
				   , std::numeric_limits<double>::max() );
	}

	void Menu::showSettings() const {
		std::cout << "\tVertex id border ";
		outputRange( graphSettings.vertexIdBorder );

		std::cout << "\tVertex color border ";
		outputRange( graphSettings.vertexColorBorder );

		std::cout << "\tEdge weight border ";
		outputRange( graphSettings.edgeWeightBorder );
	}

	template<class Range>
		void Menu::outputRange( const Range &range ) const {
			std::cout << range.first << " - " << range.second << ".\n";
		}

	void Menu::convert() {
		std::cout << "convert\n";
		creator.convertToGraph( graphSettings );
	}

	void Menu::showGraph() const {
		std::string command = ( "sensible-browser " );

		auto graphPath = creator.getGraphPath();

		command.append( graphPath );

		system( command.c_str() );
	}

}
