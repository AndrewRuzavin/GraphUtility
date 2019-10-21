#pragma once

namespace GraphCreator {
	
	struct HeaderInfo {
			size_t vertexNum = 0;
			size_t edgeNum = 0;
	};
	
	struct VertexInfo {
			size_t id = 0;
			size_t color = 0;
	};
	
	struct EdgeInfo {
			size_t srcId = 0;
			size_t dstId = 0;
			double weight = 0;

			bool operator==( const EdgeInfo &obj ) {
				return this->weight == obj.weight;
			}
	};
	
}
