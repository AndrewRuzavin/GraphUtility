#pragma once
#include <exception>
#include <string>

namespace GraphCreator {
	
	class FileException : public std::exception {
		public:
			enum ExceptionType {
				FileNotFound,
				WrongFormat,
				FileNotOpen
			};
			
			explicit FileException( const std::string &fileName, ExceptionType eType ) 
					: fileName( std::move( fileName ) ), eType( eType ) {}
			
			const char* what() const _GLIBCXX_USE_NOEXCEPT override;
			
		private:
			const char* getFileNotFoundStr() const;
			void addFilePath( std::string &str ) const;
			const char* getWrongFormatStr() const;
			const char* getNotOpenStr() const;
			
			std::string fileName;
			mutable std::string errStr;
			ExceptionType eType;
	};

}
