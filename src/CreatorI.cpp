#include "CreatorI.hpp"
#include <iostream>
#include "FileException.hpp"

namespace GraphCreator {
	
	CreatorI::~CreatorI() {}
	
	void CreatorI::placeCurrentDir( const std::string &currentDir ) {
		this->currentDir = takeDirPath( currentDir );
	}
	
	void CreatorI::convert() {
		converter->convert();
	}
	
	void CreatorI::exceptionHandler( const std::exception &e ) const {
		auto qwe = e.what();
		std::cout << "\nERROR: " << e.what() << std::endl;
		exit( 1 );
	}
	
	std::unique_ptr<LoaderI> CreatorI::takeLoader() const {
		auto loader = createLoader();
		loader->load();
		return loader;
	}
		
	std::string CreatorI::takeNameOfFile() const {
		auto posOfNameStart = filePath.find_last_of( "/" ) + 1;
		auto posOfNameEnd = filePath.find_last_of( "." );
		
		return std::string( std::begin( filePath ) + posOfNameStart
							  , std::begin( filePath ) + posOfNameEnd );
	}
	
	std::string CreatorI::takeDirPath( const std::string &currentDir ) const {
		
		auto posOfEndPath = currentDir.find_last_of( "/" ) + 1;
		
		return std::string( std::begin( currentDir )
							  , std::begin( currentDir ) + posOfEndPath );
	}
}
