#pragma once
#include "SaverI.hpp"
#include <fstream>
#include <vector>
#include <map>

namespace GraphCreator {

	class Saver : public SaverI {
			enum FieldsPart {
				HEADER_START,
				UNIT_OPEN,
				UNIT_CLOSE,
				EOS,
				QMARK,
				ELEM_OPEN,
				ELEM_CLOSE,
				EDGE,
				COLOR,
				LABEL,
				INDENT,
				PENWIDTH,

				AMOUNT_OF_ELEMS
			};
			using FileFieldPartElem = std::string;
			using FileFieldParts = std::vector<FileFieldPartElem>;
			
		public:
			explicit Saver( const std::string &dirPath, const std::string &fileName );
			~Saver();
			
			void open() override;
			bool isOpen() const override;
			
			void writeVertex( const VertexInfo &vertex ) override;
			void writeEdge( const EdgeInfo &edge ) override;
			void close() override;
			
		private:
			void fillFieldParts();
			void createDir() const;
			void createFullPath();
			void fillHeader();
			void closeAllUnits();
			void forceClose() const override;
			std::string getUnitOpenPart() const;
			std::string getUnitClosePart() const;
			std::string getNewLine( FieldsPart partType ) const;
			std::string getIndent() const;
			const std::string& getPart( FieldsPart partType ) const;
			
			const std::string& takeColor( size_t colorId );
			void addNewColor( const size_t colorId );
			std::string createColor() const;
			__uint8_t getRandValue( const __uint8_t minValue, const __uint8_t maxValue ) const;
			std::string doubleToStr( double value );
			
			mutable std::ofstream ofs;
			FileFieldParts fieldParts;
			mutable int indentNum = 0;
			std::map<__uint8_t, std::string> colors;
			const short cNodeThickness = 2;
	};

}
