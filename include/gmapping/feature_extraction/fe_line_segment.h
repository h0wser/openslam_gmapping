#ifndef FE_LINE_SEGMENT_H
#define FE_LINE_SEGMENT_H

#include "gmapping/feature_extraction/feature_extractor.h"
#include "gmapping/feature_extraction/line_feature.h"

class FE_LineSegment : public FeatureExtractor {
	public:
		FE_LineSegment();
		virtual ~FE_LineSegment();

		virtual double * extract_features(double* readings, unsigned int size);

		void setupLineFeatures();

	private:
		line_feature::LineFeature m_line_feature;
};

#endif // FE_LINE_SEGMENT_H
