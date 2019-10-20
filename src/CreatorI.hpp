#pragma once
#include <memory>
#include <src/LoaderI.hpp>
#include <src/ConverterI.hpp>
#include <src/SaverI.hpp>

namespace GraphCreator {
	
	class CreatorI {
		public:
			CreatorI( const std::string &currentDir, const std::string &filePath );
			virtual ~CreatorI() = 0;
			
			virtual std::unique_ptr<ConverterI> takeConverter() const;

			void convertToGraph();

			std::string getGraphPath() const;

		private:
			std::string takeDirPath( const std::string &currentDir ) const;

		protected:
			std::string takeNameOfFile() const;
			
			virtual std::unique_ptr<LoaderI> createLoader() const = 0;
			virtual std::unique_ptr<SaverI> createSaver() const = 0;
			virtual std::unique_ptr<ConverterI> createConverter( std::unique_ptr<LoaderI> loader
																 , std::unique_ptr<SaverI> saver  ) const = 0;
			
			virtual std::unique_ptr<LoaderI> takeLoader() const;

			std::string currentDir;
			std::string filePath;
			std::string graphPath;
	};
	
}
