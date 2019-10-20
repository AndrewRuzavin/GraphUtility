#include "GraphCreator.hpp"

namespace GraphCreator {

	GraphCreator::GraphCreator( const std::string &currentDir, const std::string &filePath )
			: CreatorI( currentDir, filePath ) {}
	
	std::unique_ptr<LoaderI> GraphCreator::createLoader() const {
		return std::make_unique<Loader>( filePath );
	}

	std::unique_ptr<SaverI> GraphCreator::createSaver() const {
		const auto fileName = takeNameOfFile();
		return std::make_unique<Saver>( currentDir, fileName );
	}
	
	std::unique_ptr<ConverterI> GraphCreator::createConverter( std::unique_ptr<LoaderI> loader
												 , std::unique_ptr<SaverI> saver ) const {
		
		return std::make_unique<Converter>( loader, saver );
	}
}
