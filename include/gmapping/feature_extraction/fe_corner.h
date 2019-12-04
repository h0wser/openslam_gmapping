#ifndef FE_CORNER_H
#define FE_CORNER_H

#include "gmapping/feature_extraction/feature_extractor.h"

class FE_Corner : FeatureExtractor {
	public:
		FE_Corner();
		virtual ~FE_Corner();

		virtual unsigned int extract_features(double* readings, unsigned int size);
};

#endif // FE_CORNER_H
