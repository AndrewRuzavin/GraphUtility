#include "GraphCreator.hpp"
#include <iostream>

namespace GraphCreator {
	
	
	void GraphCreator::exec( const std::string &currentDir, const std::string &filePath ) {
		placeCurrentDir( currentDir );
		this->filePath = filePath;
		
		try {
			execTry();			
		}
		catch( FileException &e ) {
			exceptionHandler( e );
		}
	}
	
	void GraphCreator::execTry() {
		auto loader = takeLoader();
		auto saver = createSaver();
		converter = createConverter( std::move( loader ), std::move( saver ) );
		
		menu();
	}
	
	void GraphCreator::menu() {
		
		outputInfo();
		while ( true ) {
			
			convert();
			break;
		}
	}
	
	void GraphCreator::outputInfo() const {
		const auto vNum = converter->getVNum();
		const auto eNum = converter->getENum();
		std::cout << "Num of vertices: " << vNum << "\tNum of edges: " << eNum << "\n";
	}
	
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
