#include "Loader.hpp"

#include <set>

namespace GraphCreator {
	
	Loader::Loader( const std::string &filePath ) 
			: LoaderI( filePath ) {
		
		fillFileHeaderFields();
		fillVertexInfoFields();
		fillEdgeInfoFields();
	}
	
	void Loader::fillFileHeaderFields() {
		fileFieldsInfo.fileHeaderFields.clear();
		fileFieldsInfo.fileHeaderFields.push_back( "=====\n" );
		fileFieldsInfo.fileHeaderFields.push_back( "V = " );
		fileFieldsInfo.fileHeaderFields.push_back( " E = " );
		fileFieldsInfo.fileHeaderFields.push_back( "\n" );
	}
	
	void Loader::fillVertexInfoFields() {
		fileFieldsInfo.fileVertexInfoFields.push_back( ", {" );
		fileFieldsInfo.fileVertexInfoFields.push_back( ", " );
		fileFieldsInfo.fileVertexInfoFields.push_back( "}" );
	}
	
	void Loader::fillEdgeInfoFields() {
		fileFieldsInfo.fileEdgeInfoFields.push_back( ", {" );
		fileFieldsInfo.fileEdgeInfoFields.push_back( ", " );
		fileFieldsInfo.fileEdgeInfoFields.push_back( ", " );
		fileFieldsInfo.fileEdgeInfoFields.push_back( "}" );
	}
		
	void Loader::load() {
		readContents();
		fillHeaderFields();
	}
	
	void Loader::readContents() {
		RAIILoader loader( filePath, *this );
		loader.open();
		isLoadedFlag = true;
		contents = loader.read();
		contentsStr = contents.str();
	}
	
	void Loader::fillHeaderFields() {
		
		auto fieldIter = std::begin( fileFieldsInfo.fileHeaderFields ) + 1;
		
		skipNext( fileFieldsInfo.fileHeaderFields, fieldIter );
		fileFieldsInfo.headerInfo.vertexNum = readNextInfo( fileFieldsInfo.fileHeaderFields, fieldIter );
		fileFieldsInfo.headerInfo.edgeNum = readNextInfo( fileFieldsInfo.fileHeaderFields, fieldIter );
		
		if ( !isThisTheEnd( fileFieldsInfo.fileHeaderFields, fieldIter )
				|| !readValuesAreCorrect() ) {

			throwException( FileException::WrongFormat );
		}
	}
	
	void Loader::skipNext( const FileFieldFormat &format, FileFieldFormatIter &fieldIter ) {
		readValue( format, fieldIter
				, []( const auto &firstPos
					, const auto &secondPos ) {} );
	}
	
	template<class Handler>
		void Loader::readValue( const FileFieldFormat &format, FileFieldFormatIter &fieldIter, Handler handler ) {
			
			if ( std::end( format ) == fieldIter ) {
				throwException( FileException::WrongFormat );
			}
			
			readNext( *(fieldIter - 1)
					  , *fieldIter
					  , handler );
			
			++fieldIter;
		}
	
	template<class Handler>
		void Loader::readNext( const std::string &currentField, const std::string &nextField, Handler handler ) {
			auto startIndex = takeIndex( currentField, fileFieldsInfo.currentIndex );
			fileFieldsInfo.currentIndex = takeIndex( nextField
													 , startIndex + currentField.size() );
			
			handler( startIndex + currentField.size()
					 , fileFieldsInfo.currentIndex );
		}
	
	size_t Loader::takeIndex( const std::string &str, const size_t pos ) const {
		const auto index = contentsStr.find( str, pos );
		
		if ( std::string::npos == index ) {
			throwException( FileException::WrongFormat );
		} else {
			return index;
		}
	}
	
	double Loader::takeDNumber( const size_t start, const size_t end ) const {

		auto fieldNum = strNum( start, end );

		return std::stod( fieldNum );
	}

	std::string Loader::strNum( const size_t start, const size_t end ) const {
		auto valStart = std::begin( contentsStr ) + start;
		auto valEnd = std::begin( contentsStr ) + end;

		std::string resultStr( valStart, valEnd );
		return resultStr;
	}
	
	std::list<EdgeInfo> Loader::readEdges() {
		auto buf = fileFieldsInfo;

		while( !isVertexInfoEnd() ) {
			readNextVertexInfo();
		}

		std::list<EdgeInfo> edges;
		while( !isEdgeInfoEnd() ) {
			auto edge = readNextEdgeInfo();
			edges.push_back( edge );
		}
		edges.unique();

		fileFieldsInfo = buf;

		return edges;
	}

	VertexInfo Loader::readNextVertexInfo() {
		processingAttempt();
		VertexInfo info;
		if ( isVertexInfoEnd() ) {
			return info;
		}
		
		auto &format = fileFieldsInfo.fileVertexInfoFields;
		auto fieldIter = std::begin( format ) + 1;		
		
		info.id = readNextInfo( format, fieldIter );
		info.color = readNextInfo( format, fieldIter );
		
		++fileFieldsInfo.numOfVerticesRead;
		
		return info;
	}
		
	size_t Loader::readNextInfo( const FileFieldFormat &format, FileFieldFormatIter &fieldIter ) {
		size_t value = 0;
		readValue( format, fieldIter
				, [this, &value]( const auto &firstPos
					, const auto &secondPos ) {
							value = takeNumber( firstPos, secondPos );
						} );
		
		return value;
	}
	
	size_t Loader::takeNumber( const size_t start, const size_t end ) const {
		auto fieldNum = strNum( start, end );
		return std::stoi( fieldNum );
	}
	
	EdgeInfo Loader::readNextEdgeInfo() {
		processingAttempt();
		EdgeInfo info;
		if ( isEdgeInfoEnd() ) {
			return info;
		}
		auto &format = fileFieldsInfo.fileEdgeInfoFields;
		auto fieldIter = std::begin( format ) + 1;		
		info.srcId = readNextInfo( format, fieldIter );
		info.dstId = readNextInfo( format, fieldIter );
		info.weight = readNextDInfo( format, fieldIter );
		
		++fileFieldsInfo.numOfEdgesRead;
		
		return info;
	}
	
	double Loader::readNextDInfo( const FileFieldFormat &format, FileFieldFormatIter &fieldIter ) {
		double value = 0;
		readValue( format, fieldIter
				, [this, &value]( const auto &firstPos
					, const auto &secondPos ) {
							value = takeDNumber( firstPos, secondPos );
						} );
		
		return value;
	}

}
