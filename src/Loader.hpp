#pragma once
#include "LoaderI.hpp"

namespace GraphCreator {
	
	class Loader : public LoaderI {
		public:
			Loader( const std::string &filePath );
			~Loader() = default;
			
			void load() override;
			VertexInfo readNextVertexInfo() override;
			EdgeInfo readNextEdgeInfo() override;
			
		private:
			void readContents();
			void fillFileHeaderFields() override;
			void fillVertexInfoFields() override;
			void fillEdgeInfoFields() override;
			
			void fillHeaderFields();
			void skipNext( const FileFieldFormat &format, FileFieldFormatIter &fieldIter );
			template<class Handler>
				void readValue( const FileFieldFormat &format, FileFieldFormatIter &fieldIter, Handler handler );
			
			template<class Handler>
				void readNext( const std::string &currentField, const std::string &nextField, Handler handler );
			size_t takeIndex( const std::string &str, const size_t pos ) const override;
			std::string strNum( const size_t start, const size_t end ) const;
			double takeDNumber( const size_t start, const size_t end ) const;
			
			VertexInfo readNextInfo();
			
			size_t readNextInfo( const FileFieldFormat &format, FileFieldFormatIter &fieldIter );
			size_t takeNumber( const size_t start, const size_t end ) const override;
			double readNextDInfo( const FileFieldFormat &format, FileFieldFormatIter &fieldIter );
	};
	
}
