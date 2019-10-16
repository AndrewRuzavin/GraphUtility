#include "SaverI.hpp"

namespace GraphCreator {
	
	const std::string SaverI::dirName = "resultFiles/";	
//	const std::string SaverI::formatName = ".gv";
	const std::string SaverI::formatName = ".dot";
	
	SaverI::SaverI( const std::string &dirPath, const std::string &fileName ) 
			: dirPath( dirPath ), fileName( fileName ) {}
	
	SaverI::~SaverI() {}
	
	std::string SaverI::getFullName() const {
		return fullFileName;
	}
	
	void SaverI::processingAttempt() const {
		if( !isOpen() ) {
			throwException( FileException::FileNotOpen );
		}
	}
	
	void SaverI::throwException( FileException::ExceptionType type ) const {
		forceClose();
		throw FileException( getFullName(), type );
	}	
	
}
