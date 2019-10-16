#pragma once
#include "ConverterI.hpp"

namespace GraphCreator {
	
	class Converter : public ConverterI {
		public:
			explicit Converter( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver );
			
			void convert() override;
			
			size_t getVNum() const override;
			size_t getENum() const override;
			
		private:
			void convertVertices();
			void convertEdges();
			bool saveImageGV( const std::string &filePath ) const;
			std::string takeImgPath( const std::string &filePath ) const;
			
			static const std::string IMG_FORMAT;
	};
	
}
