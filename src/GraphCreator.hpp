#pragma once
#include "CreatorI.hpp"
#include "Loader.hpp"
#include "Converter.hpp"
#include "Saver.hpp"

namespace GraphCreator {
	
	class GraphCreator : public CreatorI {
		public:
			
			void exec( const std::string &currentDir, const std::string &filePath ) override;
			
		private:
			void execTry();
			void menu();
			void outputInfo() const;
			
			std::unique_ptr<LoaderI> createLoader() const override;
			std::unique_ptr<SaverI> createSaver() const override;
			std::unique_ptr<ConverterI> createConverter( std::unique_ptr<LoaderI> loader
														 , std::unique_ptr<SaverI> saver ) const override;						
	};
	
	inline std::unique_ptr<CreatorI> createCreator() {
		return std::make_unique<GraphCreator>();
	}
	
}
