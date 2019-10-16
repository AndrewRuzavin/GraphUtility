#pragma once
#include "LoaderI.hpp"
#include "SaverI.hpp"
#include <memory>

namespace GraphCreator {
	
	class ConverterI {
		public:
	//		using FileContents = std::stringstream;
	
			explicit ConverterI( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver );
			virtual ~ConverterI() = 0;
			
			virtual void convert() = 0;
			
			virtual size_t getVNum() const = 0;
			virtual size_t getENum() const = 0;			
		
		protected:
			std::unique_ptr<LoaderI> loader;
			std::unique_ptr<SaverI> saver;
	};
	
}
