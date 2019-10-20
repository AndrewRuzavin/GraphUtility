#pragma once
#include "GraphCreator.hpp"

namespace GraphCreator {

	class Menu {
		public:
			Menu( const std::string &currentDir, const std::string &filePath );

			void exec();

		private:
			void exceptionHandler( const std::exception &e ) const;
			void execTry();
			void outputInfo() const;
			void showGraph() const;

			GraphCreator creator;
	};

}
