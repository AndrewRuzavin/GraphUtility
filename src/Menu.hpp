#pragma once
#include "GraphCreator.hpp"
#include <functional>

namespace GraphCreator {

	class Menu {
			enum CommandsId {
				FIRST_COMMAND_NUM,

				HELP = FIRST_COMMAND_NUM,
				CR_ID,
				CR_COLOR,
				CR_WEIGHT,
				CONVERT,
				SHOW,
				EXIT,

				LAST_COMMAND_ID = EXIT,
				AMOUNT_OF_COMMANDS
			};

			struct Command {
					std::function<void()> handler;
					std::string name;
					std::string info;
			};

//			using Handler = void(*)();
////			using THandler = this::THandler;

//			using Fun = void (*)();
//			using q = void (Menu::Fun*)();

//			using Handler = function
//			void ( Menu::*fun )();
//			using Handler = Menu::*fun;

		public:
			Menu( const std::string &currentDir, const std::string &filePath );

			void exec();

		private:
			void fillCommands();
			void exceptionHandler( const std::exception &e ) const;
			void execTry();
			bool menuSelector();
			std::string takeNextCommand() const;
			void execCommand( const std::string &inputCommand ) const;
			void outputInfo() const;
			void outputAllCommandInfos() const;
			void changeRangeId() const;
			void changeRangeColor() const;
			void changeRangeWeight() const;
			void convert();
			void showGraph() const;

			GraphCreator creator;
//			std::array<std::string, AMOUNT_OF_COMMANDS> commands;
//			std::array<std::pair<std::string, Handler>, AMOUNT_OF_COMMANDS> commands;
			std::array<Command, AMOUNT_OF_COMMANDS> commands;


//			std::array<std::pair<std::string, Func::Fun>, AMOUNT_OF_COMMANDS> commands;
	};

}
