#include "SaverI.hpp"

namespace GraphCreator {

	const std::string SaverI::DIR_NAME = "resultFiles/";
	const std::string FORMAT_NAME = "circo";

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
