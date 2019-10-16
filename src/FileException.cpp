#include "FileException.hpp"

namespace GraphCreator {
	
	const char* FileException::what() const _GLIBCXX_USE_NOEXCEPT {
		
		switch( eType ) {
			case FileNotFound:
				return getFileNotFoundStr();
			case WrongFormat:
				return getWrongFormatStr();
			case FileNotOpen:
				return getNotOpenStr();
			default:
				return fileName.c_str();
		}
	}

	const char* FileException::getFileNotFoundStr() const {
		if ( errStr.empty() ) {
			errStr.append( "File not found. File name \"" );
			errStr.append( fileName );
			errStr.append( "\"." );
		}
		return errStr.c_str();
	}
	
	void FileException::addFilePath( std::string &str ) const {
		errStr.append( " File name \"" );
		errStr.append( fileName );
		errStr.append( "\"." );
	}
	
	const char* FileException::getWrongFormatStr() const {
		if ( errStr.empty() ) {
			errStr.append( "File contains invalid format. File name \"" );
			errStr.append( fileName );
			errStr.append( "\"." );
		}				
		return errStr.c_str();
	}
	
	const char* FileException::getNotOpenStr() const {
		if ( errStr.empty() ) {
			errStr.append( "File not open." );
			addFilePath( errStr );			
		}				
		return errStr.c_str();
	}
	
}
