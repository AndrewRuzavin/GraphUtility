#pragma once
#include <memory>
#include <src/LoaderI.hpp>
#include <src/ConverterI.hpp>
#include <src/SaverI.hpp>

namespace GraphCreator {
	
	class CreatorI {
		public:
			CreatorI() = default;
			virtual ~CreatorI() = 0;
			
			virtual void exec( const std::string &currentDir, const std::string &filePath ) = 0;
			
		protected:
			void exceptionHandler( const std::exception &e ) const;
			void placeCurrentDir( const std::string &currentDir );
			std::string takeNameOfFile() const;
			void convert();
			
			virtual std::unique_ptr<LoaderI> createLoader() const = 0;
			virtual std::unique_ptr<SaverI> createSaver() const = 0;
			virtual std::unique_ptr<ConverterI> createConverter( std::unique_ptr<LoaderI> loader
																 , std::unique_ptr<SaverI> saver  ) const = 0;
			
			virtual std::unique_ptr<LoaderI> takeLoader() const;
			
			std::string currentDir;
			std::string filePath;
			std::unique_ptr<ConverterI> converter;
			
		private:
			std::string takeDirPath( const std::string &currentDir ) const;			
	};
	
}
