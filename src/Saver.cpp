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
		fieldParts[HEADER_START] = "digraph ";
		fieldParts[UNIT_OPEN] = "{";
		fieldParts[UNIT_CLOSE] = "}";
		fieldParts[EOS] = ";\n";
		fieldParts[QMARK] = "\"";
		fieldParts[ELEM_OPEN] = " [";
		fieldParts[ELEM_CLOSE] = "]";
		fieldParts[EDGE] = " -> ";
		fieldParts[COLOR] = "color=\"#";
		fieldParts[LABEL] = "label=";
		fieldParts[INDENT] = "\t";
		fieldParts[PENWIDTH] = "penwidth=";
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
		for ( ; indentNum > 0; ) {
			ofs << getUnitClosePart() << "\n";
		}
	}
	
	void Saver::forceClose() const {
		if ( isOpen() ) {
			ofs.close();
		}
	}
	
	std::string Saver::getUnitOpenPart() const {
		++indentNum;
		return getPart( UNIT_OPEN );
	}
	
	std::string Saver::getUnitClosePart() const {
		if ( indentNum > 0) {
			--indentNum;
			return getIndent() + getPart( UNIT_CLOSE );
		} else {
			return std::string();
		}
	}
	
	std::string Saver::getNewLine( FieldsPart partType ) const {
		return getIndent() + getPart( partType );
	}
	
	std::string Saver::getIndent() const {
		std::string indentStr;
		for ( auto i = 0; i < indentNum; ++i ) {
			indentStr.append( getPart( INDENT ) );
		}
		return indentStr;
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
		outputStr.append( getPart( PENWIDTH ) );
		outputStr.append( std::to_string( cNodeThickness ) );
		outputStr.append( getPart( ELEM_CLOSE ) );
		outputStr.append( getPart( EOS ) );
		
		ofs.write( outputStr.c_str(), outputStr.size() );
	}
	
	void Saver::writeEdge( const EdgeInfo &edge ) {
		processingAttempt();
		
		std::string outputStr( getIndent() );
		outputStr.append( std::to_string( edge.srcId ) );
		outputStr.append( getPart( EDGE ) );
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
		colors[colorId] = createColor();
	}

	std::string Saver::createColor() const {
		const __uint8_t minValue = 0;
		const __uint8_t maxValue = 255;
		const __uint8_t minDiffCoef = 50;
		__uint8_t r, g, b;
		do {
			r = getRandValue( minValue, maxValue );
			g = getRandValue( minValue, maxValue );
			b = getRandValue( minValue, maxValue );

			auto bufVal0 = r > g ? r % g : g % r;
			auto bufVal1 = r > b ? r % b : b % r;
			auto bufVal2 = g > b ? g % b: b % g;

			if ( ( bufVal0 + bufVal1 + bufVal2 ) > minDiffCoef ) {
				break;
			}

		} while ( true );

		__uint32_t color = r;
		color = ( color << 8 ) + g;
		color = ( color << 8 ) + b;
		color = ( color << 8 ) + 255;

		std::stringstream stream;
		stream << std::hex << color;
		return std::string( stream.str() );
	}

	__uint8_t Saver::getRandValue( const __uint8_t minValue, const __uint8_t maxValue ) const {
		return rand() % ( maxValue - minValue ) + minValue + 1;
	}

	std::string Saver::doubleToStr( double value ) {
		std::string str( std::to_string( value ) );
		if ( str.empty() ) {
			return str;
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
		
		return str;
	}
}
