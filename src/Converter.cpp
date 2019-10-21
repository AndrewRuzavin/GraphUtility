#include "Converter.hpp"
#include "FileException.hpp"

namespace GraphCreator {
	
	const std::string Converter::GRAPH_FORMAT = "svg";

	Converter::Converter( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver ) 
			: ConverterI( loader, saver ) {}
	
	size_t Converter::getVNum() const {
		return loader->getVNum();
	}
	
	size_t Converter::getENum() const {
		return loader->getENum();
	}
	
	void Converter::convertToGraph( const GraphSettingFields &settings ) {
		createGraphInputFile( settings );
		saveGraph( saver->getFullName() );
	}
	
	void Converter::createGraphInputFile( const GraphSettingFields &settings ) {
		const auto edgesWeights = takeEdgesWeights( settings );

		saver->open();

		convertVertices( settings );
		convertEdges( settings );

		saver->close();
	}

	std::list<double> Converter::takeEdgesWeights( const GraphSettingFields &settings  ) const {
		auto edges = loader->readEdges();
		std::list<double> edgesWeight;
		if ( !edges.empty() ) {
			for ( const auto &edge : edges ) {
				if ( checkEdge( edge, settings ) ) {
					edgesWeight.push_back( edge.weight );
				}
			}
		}
		edgesWeight.unique();
		return edgesWeight;
	}

	void Converter::convertVertices( const GraphSettingFields &settings ) {
		while( !loader->isVertexInfoEnd() ) {
			auto vertex = loader->readNextVertexInfo();

			if ( checkVertex( vertex, settings ) ) {
				saver->writeVertex( vertex );
			}
		}
	}
	
	bool Converter::checkVertex( const VertexInfo &vertex, const GraphSettingFields &settings ) const {
		vertex.id;

		if ( !compare( vertex.id, settings.vertexIdBorder ) ) {
			return false;
		}
		if ( !compare( static_cast<short>( vertex.color ), settings.vertexColorBorder ) ) {
			return false;
		}

		return true;
	}

	template<class T>
		bool Converter::compare( const T &val, const std::pair<T, T> &range ) const {
			return range.first <= val
					&& val <= range.second;
		}

	void Converter::convertEdges( const GraphSettingFields &settings ) {
		while( !loader->isEdgeInfoEnd() ) {
			auto edge = loader->readNextEdgeInfo();

			if ( checkEdge( edge, settings ) ) {
				saver->writeEdge( edge );
			}
		}
	}

	bool Converter::checkEdge( const EdgeInfo &edge, const GraphSettingFields &settings ) const {
		if ( !compare( edge.srcId, settings.vertexIdBorder ) ) {
			return false;
		}
		if ( !compare( edge.dstId, settings.vertexIdBorder ) ) {
			return false;
		}
		if ( !compare( edge.weight, settings.edgeWeightBorder ) ) {
			return false;
		}

		return true;
	}

	static int reader( void *chan, char *buf, int bufsize ) {
		return fread(buf, 1, bufsize, (FILE*)chan);
	}

	bool Converter::saveGraph( const std::string &filePath ) {
		FILE *fp = fopen( filePath.c_str(), "r" );
		auto g = takeGraph( fp );
		GVC_t *gvc = gvContext();

		gvLayout( gvc, g, FORMAT_NAME.c_str() );

		graphPath = takeGraphPath( filePath );
		gvRender( gvc, g, GRAPH_FORMAT.c_str(), fopen( graphPath.c_str(), "w" ) );
		gvFreeLayout( gvc, g );
		agclose( g );
		return ( gvFreeContext( gvc ) );
	}
	
	Converter::Graph Converter::takeGraph( FILE *fp ) const {
		Agdisc_t mydisc;
		Agiodisc_t myiodisc;

		mydisc.mem = NULL;  // use system default
		mydisc.id = NULL;   // use system default
		mydisc.io = &myiodisc;
		myiodisc.afread = reader;
		myiodisc.putstr = NULL;  // only need to set if calling gvRender()
		myiodisc.flush = NULL;   // only need to set if calling gvRender()

		return agread( fp, &mydisc );
	}

	std::string Converter::takeGraphPath( const std::string &filePath ) const {
		auto pos = filePath.find_last_of( '.' ) + 1;
		std::string resGraphPath( std::begin( filePath )
							 , std::begin( filePath ) + pos );
		resGraphPath.append( GRAPH_FORMAT );
		
		return resGraphPath;
	}

	std::string Converter::getGraphPath() const {
		return graphPath;
	}

}
