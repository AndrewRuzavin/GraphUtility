#include "Saver.hpp"
#include "FileException.hpp"
#include <time.h>
#include <sstream>

namespace GraphCreator {
	
	Saver::Saver( const std::string &dirPath, const std::string &fileName ) 
			: SaverI( dirPath, fileName ) {
		srand( time( NULL ) );
	}
	
	Saver::~Saver() {
		close();
	}

	void Saver::open() {		
		fillFieldParts();
		createDir();
		createFullPath();
		indentNum = 0;
		
		ofs.open( getFullName(), std::ofstream::binary );
		
		fillHeader();
		
		if ( !ofs.is_open() ) {
			throw FileException( getFullName(), FileException::FileNotOpen );
		}
	}
	
	void Saver::fillFieldParts() {
		fieldParts.clear();
		fieldParts.reserve( AMOUNT_OF_ELEMS );
		fieldParts.push_back( "graph " );		//	HEADER_START
		fieldParts.push_back( "{" );			//	UNIT_OPEN
		fieldParts.push_back( "}" );			//	UNIT_CLOSE
		fieldParts.push_back( ";\n" );			//	EOS
		fieldParts.push_back( "\"" );			//	QMARK
		fieldParts.push_back( " [" );			//	ELEM_OPEN
		fieldParts.push_back( "]" );			//	ELEM_CLOSE
		fieldParts.push_back( " -> " );			//	UNIDIR_EDGE
		fieldParts.push_back( " -- " );			//	BIDIE_EDGE
		fieldParts.push_back( "color=\"#" );	//	COLOR
		fieldParts.push_back( "label=" );		//	LABEL
		fieldParts.push_back( "\t" );			//	INDENT
	}
	
	void Saver::createDir() const {
		std::string fullDirPath( "mkdir -p " + dirPath + dirName );
		system( fullDirPath.c_str() );
	}
	
	void Saver::createFullPath() {
		fullFileName.clear();
		fullFileName.append( dirName );
		fullFileName.append( fileName );
		fullFileName.append( formatName );
	}
	
	void Saver::fillHeader() {
		ofs << getNewLine( HEADER_START ) << fileName << " ";
		ofs << getUnitOpenPart() << "\n";
	}
	
	void Saver::close() {
		if ( isOpen() ) {
			closeAllUnits();
			ofs.close();
		}
	}
		
	void Saver::closeAllUnits() {
		for ( ; indentNum > 0; --indentNum ) {
			ofs << getIndent() << getUnitClosePart() << "\n";
		}
	}
	
	void Saver::forceClose() const {
		if ( isOpen() ) {
			ofs.close();
		}
	}
	
	std::string Saver::getUnitOpenPart() const {
		++indentNum;
		return std::move( getPart( UNIT_OPEN ) );
	}
	
	std::string Saver::getUnitClosePart() const {
		
		if ( indentNum > 0) {
			--indentNum;
			return std::move( getIndent() + getPart( UNIT_CLOSE ) );
		} else {
			return std::move( std::string() );
		}
	}
	
	std::string Saver::getNewLine( FieldsPart partType ) const {
		return std::move( getIndent() + getPart( partType ) );
	}
	
	std::string Saver::getIndent() const {
		std::string indentStr;
		for ( auto i = 0; i < indentNum; ++i ) {
			indentStr.append( getPart( INDENT ) );
		}
		return std::move( indentStr );
	}
	
	const std::string& Saver::getPart( FieldsPart partType ) const {
		return fieldParts.at( partType );
	}
	
	bool Saver::isOpen() const {
		return ofs.is_open();
	}
	
	void Saver::writeVertex( const VertexInfo &vertex ) {
		processingAttempt();
		
		std::string outputStr( getIndent() );
		outputStr.append( std::to_string( vertex.id ) );
		outputStr.append( getPart( ELEM_OPEN ) );
		outputStr.append( getPart( COLOR ) );
		outputStr.append( takeColor( vertex.color ) );
		outputStr.append( getPart( QMARK ) );		
		outputStr.append( getPart( ELEM_CLOSE ) );
		outputStr.append( getPart( EOS ) );
		
		ofs.write( outputStr.c_str(), outputStr.size() );
	}
	
	void Saver::writeEdge( const EdgeInfo &edge ) {
		processingAttempt();
		
		std::string outputStr( getIndent() );
		outputStr.append( std::to_string( edge.srcId ) );
//		outputStr.append( getPart( UNIDIR_EDGE ) );	//Graphviz не ест "->"
		outputStr.append( getPart( BIDIE_EDGE ) );
		
		outputStr.append( std::to_string( edge.dstId ) );
		outputStr.append( getPart( ELEM_OPEN ) );
		outputStr.append( getPart( LABEL ) );
		outputStr.append( doubleToStr( edge.weight ) );
		outputStr.append( getPart( ELEM_CLOSE ) );
		outputStr.append( getPart( EOS ) );
		
		ofs.write( outputStr.c_str(), outputStr.size() );
	}
	
	const std::string& Saver::takeColor( const size_t colorId ) {
		if ( std::end( colors ) == colors.find( colorId ) ) {
			addNewColor( colorId );
		}
		return colors[colorId];
	}
	
	void Saver::addNewColor( const size_t colorId ) {
		auto minValue = 40;
		auto maxValue = 256;
		
		auto r = rand() % ( maxValue - minValue ) + minValue;
		auto b = rand() % ( maxValue - minValue ) + minValue;
		auto g = rand() % ( maxValue - minValue ) + minValue;
		
		__int64_t color = r;
		color = ( color << 8 ) + g;
		color = ( color << 8 ) + b;
		color = ( color << 8 ) + 255;
		
		std::stringstream stream;
		stream << std::hex << color;
		std::string colorStr( stream.str() );
		
		colors[colorId] = colorStr;
	}

	std::string Saver::doubleToStr( double value ) {
		std::string str( std::to_string( value ) );
		if ( str.empty() ) {
			return std::move( str );
		}
		for ( auto iter = std::end( str ) - 1; iter != std::begin( str ); --iter ) {
			if ( ( '0' == *iter ) 
					|| ( '.' == *iter ) ) {
				
				auto c = *iter;
				str.erase( iter );
				if ( c == '.') {
					break;
				}
			} else {
				break;
			}
		}
		
		return std::move( str );
	}
}
