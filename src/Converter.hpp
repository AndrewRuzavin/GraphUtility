#pragma once
#include "ConverterI.hpp"
#include <graphviz/gvc.h>

namespace GraphCreator {

	class Converter : public ConverterI {
			using Graph = Agraph_t*;
		public:
			explicit Converter( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver );
			
			void convertToGraph() override;
			
			size_t getVNum() const override;
			size_t getENum() const override;

			std::string getGraphPath() const override;

		private:
			void createGraphInputFile();
			void convertVertices();
			void convertEdges();
			bool saveGraph( const std::string &filePath );
			Graph takeGraph( FILE *fp ) const;
			std::string takeGraphPath( const std::string &filePath ) const;

			static const std::string GRAPH_FORMAT;
			std::string graphPath;
	};
	
}
