#ifndef FE_LINE_SEGMENT_H
#define FE_LINE_SEGMENT_H

#include "gmapping/feature_extraction/feature_extractor.h"
#include "gmapping/feature_extraction/line_feature.h"

class FE_LineSegment : FeatureExtractor {
	public:
		FE_LineSegment();
		virtual ~FE_LineSegment();

		virtual unsigned int extract_features(double* readings, double delta_theta, unsigned int size);

	private:
		line_feature::LineFeature m_line_feature;
};

#endif // FE_LINE_SEGMENT_H
