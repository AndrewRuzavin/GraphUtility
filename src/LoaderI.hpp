#pragma once
#include <sstream>
#include <vector>
#include "FileException.hpp"
#include "InfoStructs.hpp"
#include <fstream>
#include <list>

namespace GraphCreator {
	
	class LoaderI {
		protected:
			using FileFieldFormatElem = std::string;
			using FileFieldFormat = std::vector<FileFieldFormatElem>;
			using FileFieldFormatIter = FileFieldFormat::iterator;
			
			struct FileFieldsInfo {
					FileFieldFormat fileHeaderFields;
					FileFieldFormat fileVertexInfoFields;
					FileFieldFormat fileEdgeInfoFields;
					
					size_t currentIndex = 0;
					HeaderInfo headerInfo;
					size_t numOfVerticesRead = 0;
					size_t numOfEdgesRead = 0;
					
			} fileFieldsInfo;


			class RAIILoader {
				public:
					explicit RAIILoader( const std::string &filePath, LoaderI &loader ) 
						: filePath( filePath ), loader( loader ) {}
					
					~RAIILoader() {
						is.close();
					}
					
					void open();
					std::stringstream read();
					
				private:
					std::string filePath;
					LoaderI &loader;
					std::ifstream is;
			};
			
		public:
			explicit LoaderI( const std::string filePath );
			virtual ~LoaderI() = 0;
			
			virtual void load( const std::string &filePath );
			virtual void load() = 0;
			
			virtual std::list<EdgeInfo> readEdges() = 0;
			virtual VertexInfo readNextVertexInfo() = 0;
			virtual EdgeInfo readNextEdgeInfo() = 0;
			
			void throwException( FileException::ExceptionType type ) const;
			size_t eof() const;
			bool isThisTheEnd( const FileFieldFormat &container, const FileFieldFormatIter &iter ) const;
			bool readValuesAreCorrect() const;
			void processingAttempt() const;
			bool isVertexInfoEnd() const;
			bool isEdgeInfoEnd() const;
			std::string getFilePath() const;
			bool isLoaded() const;
			size_t getVNum() const;
			size_t getENum() const;
			void clear();
			
		protected:
			virtual void fillFileHeaderFields() = 0;
			virtual void fillVertexInfoFields() = 0;
			virtual void fillEdgeInfoFields() = 0;
			
			virtual size_t takeIndex( const std::string &str, const size_t pos ) const = 0;
			virtual size_t takeNumber( const size_t start, const size_t end ) const = 0;
			
			std::string filePath;
			std::stringstream contents;
			mutable bool isLoadedFlag = false;
			const size_t cEOFields = -1;
	};
	
}
