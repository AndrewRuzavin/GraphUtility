#pragma once
#include "LoaderI.hpp"
#include "SaverI.hpp"
#include <memory>

namespace GraphCreator {
	
	class ConverterI {
		public:
			struct GraphSettingFields {
					std::pair<size_t, size_t> vertexIdBorder;
					std::pair<__int16_t, __int16_t> vertexColorBorder;	//__int8_t достаточно, но он является
						// псевдонимом для unsigned char и при выводе, без приведения типов, выводятся кракозябры
					std::pair<double, double> edgeWeightBorder;
			};

			explicit ConverterI( std::unique_ptr<LoaderI> &loader, std::unique_ptr<SaverI> &saver );
			virtual ~ConverterI() = 0;
			
			virtual void convertToGraph( const GraphSettingFields &settings ) = 0;
			
			virtual size_t getVNum() const = 0;
			virtual size_t getENum() const = 0;

			virtual std::string getGraphPath() const = 0;

		protected:
			std::unique_ptr<LoaderI> loader;
			std::unique_ptr<SaverI> saver;
	};
	
}
