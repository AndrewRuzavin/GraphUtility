#pragma once
#include <string>
#include "InfoStructs.hpp"
#include "FileException.hpp"

namespace GraphCreator {
	
	class SaverI {
		public:
			explicit SaverI( const std::string &dirPath, const std::string &fileName );
			virtual ~SaverI() = 0;
			
			virtual void open() = 0;
			virtual bool isOpen() const = 0;
			
			virtual void writeVertex( const VertexInfo &vertex ) = 0;
			virtual void writeEdge( const EdgeInfo &edge ) = 0;
			virtual void close() = 0;
			
			std::string getFullName() const;
			
		protected:
			void processingAttempt() const;
			void throwException( FileException::ExceptionType type ) const;
			virtual void forceClose() const = 0;
			
			std::string dirPath;
			std::string fileName;
			std::string fullFileName;
			
			static const std::string DIR_NAME;
	};
	
	extern const std::string FORMAT_NAME;
}
