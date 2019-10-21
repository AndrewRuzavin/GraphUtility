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
				SHOW_SETT,
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

			using GraphSettingFields = CreatorI::GraphSettingFields;

		public:
			Menu( const std::string &currentDir, const std::string &filePath );

			void exec();

		private:
			void fillCommands();
			void exceptionHandler( const std::exception &e ) const;
			void execTry();
			void fillInfoFields();
			void outputInfo() const;
			bool menuSelector();
			std::string takeNextCommand() const;
			void execCommand( const std::string &inputCommand ) const;
			void outputAllCommandInfos() const;
			void changeRangeId();
			template<class Range, class BorderType>
				void takeRange( Range &range, const BorderType lower, const BorderType upper );
			template<class ValType, class BorderType>
				bool takeOneOfRange( ValType &val, const BorderType lower, const BorderType upper, const std::string &infoStr ) const;
			template<class ValType, class BorderType>
				bool takeValue( ValType &val, const BorderType lower, const BorderType upper ) const;
			template<class ValType>
				bool isItNum( const std::string &str ) const;
			template<class ValType>
				auto convertStrToVal( const std::string &str ) const;
			template<class ValType, class BorderType>
				bool withinTheBorder( const ValType val, const BorderType lower, const BorderType upper ) const;
			void changeRangeColor();
			void changeRangeWeight();
			void showSettings() const;
			template<class Range>
				void outputRange( const Range &range ) const;
			void convert();
			void showGraph() const;

			GraphCreator creator;
			std::array<Command, AMOUNT_OF_COMMANDS> commands;
			size_t vNum;
			size_t eNum;
			GraphSettingFields graphSettings;
			static const int COLOR_MAX_RANGE;
	};

}
