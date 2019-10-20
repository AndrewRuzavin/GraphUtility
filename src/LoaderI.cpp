#include "LoaderI.hpp"

namespace GraphCreator {
	
	//LoaderI::RAIILoader
	void LoaderI::RAIILoader::open() {
		is.open( filePath );
		if ( !is ) {
			loader.throwException( FileException::FileNotOpen );
		}
	}
	
	std::stringstream LoaderI::RAIILoader::read() {
		std::stringstream buf;
		buf << is.rdbuf();
		return buf;
	}
	
	
	//LoaderI
	LoaderI::LoaderI( const std::string filePath ) 
			: filePath( filePath ) {}
	
	LoaderI::~LoaderI() {}
	
	void LoaderI::throwException( FileException::ExceptionType type ) const {
		isLoadedFlag = false;
		throw FileException( filePath, type );
	}
	
	size_t LoaderI::eof() const {
		return cEOFields;
	}
	
	bool LoaderI::isThisTheEnd( const FileFieldFormat &container, const FileFieldFormatIter &iter ) const {
		processingAttempt();
		return std::end( container ) == iter;
	}
	
	void LoaderI::processingAttempt() const {
		if( !isLoaded() ) {
			throwException( FileException::FileNotOpen );
		}
	}
	
	bool LoaderI::isVertexInfoEnd() const {
		return getVNum() <= fileFieldsInfo.numOfVerticesRead;
	}
	
	bool LoaderI::isEdgeInfoEnd() const {
		return getENum() <= fileFieldsInfo.numOfEdgesRead;
	}
	
	std::string LoaderI::getFilePath() const {
		return filePath;
	}
	
	bool LoaderI::isLoaded() const {
		return isLoadedFlag;
	}
	
	size_t LoaderI::getVNum() const {
		return fileFieldsInfo.headerInfo.vertexNum;
	}
	
	size_t LoaderI::getENum() const {
		return fileFieldsInfo.headerInfo.edgeNum;		
	}
	
	
}
