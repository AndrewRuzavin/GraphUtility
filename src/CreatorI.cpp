#include "CreatorI.hpp"
#include "FileException.hpp"

namespace GraphCreator {
	
	CreatorI::CreatorI( const std::string &currentDir, const std::string &filePath )
			: filePath( filePath ) {

		this->currentDir = takeDirPath( currentDir );
	}

	CreatorI::~CreatorI() {}
	
	std::string CreatorI::takeDirPath( const std::string &currentDir ) const {

		auto posOfEndPath = currentDir.find_last_of( "/" ) + 1;

		return std::string( std::begin( currentDir )
							  , std::begin( currentDir ) + posOfEndPath );
	}

	void CreatorI::convertToGraph(/*need struct with diapason*/) {
		graphPath.clear();

		auto converter = takeConverter();
		converter->convertToGraph();
		graphPath = converter->getGraphPath();
	}
	
	std::unique_ptr<ConverterI> CreatorI::takeConverter() const {
		auto loader = takeLoader();
		auto saver = createSaver();
		return createConverter( std::move( loader ), std::move( saver ) );
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
	
	std::string CreatorI::getGraphPath() const {
		return graphPath;
	}

}
