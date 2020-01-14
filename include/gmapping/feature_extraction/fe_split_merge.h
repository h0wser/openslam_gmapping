#ifndef FE_SPLIT_MERGE_H
#define FE_SPLIT_MERGE_H

#include "gmapping/feature_extraction/feature_extractor.h"
#include "laser_line_extraction/line_extraction_ros.h"

class FE_SplitMerge : FeatureExtractor {
	public:
		FE_SplitMerge();
		virtual ~FE_SplitMerge();

		virtual double* extract_features(double* plainReading, unsigned int m_beams);

	private:
		line_extraction::LineExtractionROS m_line_extractor;
};

#endif // FE_SPLIT_MERGE_H
