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
				UNIDIR_EDGE,
				BIDIE_EDGE,
				COLOR,
				LABEL,
				INDENT,
				
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
			std::string doubleToStr( double value );
			
			mutable std::ofstream ofs;
			FileFieldParts fieldParts;
			mutable int indentNum = 0;
			std::map<char, std::string> colors;
	};

}
