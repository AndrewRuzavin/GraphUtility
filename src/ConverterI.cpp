#include "ConverterI.hpp"

namespace GraphCreator {
	
	ConverterI::ConverterI( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver ) 
			: loader( std::move(loader) ), saver( std::move(saver) ) {}
	
	ConverterI::~ConverterI() {}
	
}
