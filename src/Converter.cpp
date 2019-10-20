#include "Converter.hpp"
#include "FileException.hpp"
#include <iostream>

namespace GraphCreator {
	
	const std::string Converter::IMG_FORMAT = "png";
	
	Converter::Converter( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver ) 
			: ConverterI( loader, saver ) {}
	
	size_t Converter::getVNum() const {
		return loader->getVNum();
	}
	
	size_t Converter::getENum() const {
		return loader->getENum();
	}
	
	void Converter::convert() {		
		saver->open();
		
		convertVertices();
		convertEdges();
		
		saver->close();
		
		saveImageGV( saver->getFullName() );
	}
	
	void Converter::convertVertices() {
		while( !loader->isVertexInfoEnd() ) {
			auto vertex = loader->readNextVertexInfo();
			saver->writeVertex( vertex );
		}
	}
	
	void Converter::convertEdges() {
		while( !loader->isEdgeInfoEnd() ) {
			auto edge = loader->readNextEdgeInfo();
			saver->writeEdge( edge );
		}
	}

	static int reader( void *chan, char *buf, int bufsize ) {
		return fread(buf, 1, bufsize, (FILE*)chan);
	}

	bool Converter::saveImageGV( const std::string &filePath ) const {
		FILE *fp = fopen( filePath.c_str(), "r" );
		auto g = takeGraph( fp );
		GVC_t *gvc = gvContext();
		gvLayout( gvc, g, "dot" );
		
		const auto imgPath = takeImgPath( filePath );
		gvRender( gvc, g, IMG_FORMAT.c_str(), fopen( imgPath.c_str(), "w" ) );
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

	std::string Converter::takeImgPath( const std::string &filePath ) const {
		auto pos = filePath.find_last_of( '.' ) + 1;
		std::string imgPath( std::begin( filePath )
							 , std::begin( filePath ) + pos );
		imgPath.append( IMG_FORMAT );
		
		return imgPath;
	}
			
}
