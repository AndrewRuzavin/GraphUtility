#pragma once
#include "ConverterI.hpp"
#include <graphviz/gvc.h>

namespace GraphCreator {

	class Converter : public ConverterI {
			using Graph = Agraph_t*;
		public:
			explicit Converter( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver );
			
			void convertToGraph( const GraphSettingFields &settings ) override;
			
			size_t getVNum() const override;
			size_t getENum() const override;

			std::string getGraphPath() const override;

		private:
			void createGraphInputFile( const GraphSettingFields &settings );
			std::list<double> takeEdgesWeights( const GraphSettingFields &settings ) const;
			void convertVertices( const GraphSettingFields &settings );
			bool checkVertex( const VertexInfo &vertex, const GraphSettingFields &settings ) const;
			template<class T>
				bool compare( const T &val, const std::pair<T, T> &range ) const;
			void convertEdges( const GraphSettingFields &settings );
			bool checkEdge( const EdgeInfo &edge, const GraphSettingFields &settings ) const;
			bool saveGraph( const std::string &filePath );
			Graph takeGraph( FILE *fp ) const;
			std::string takeGraphPath( const std::string &filePath ) const;

			static const std::string GRAPH_FORMAT;
			std::string graphPath;
	};
	
}
