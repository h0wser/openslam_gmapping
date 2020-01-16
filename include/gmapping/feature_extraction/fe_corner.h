#ifndef FE_CORNER_H
#define FE_CORNER_H

#include "gmapping/feature_extraction/feature_extractor.h"

class FE_Corner : public FeatureExtractor {
	public:
		FE_Corner();
		virtual ~FE_Corner();

		static void polarToCartesian(unsigned int m_beam, double* plainReading,double* angleArray,double * m_xCartesian,double * m_yCartesian);

		static int cornerCheck(double* m_xCartesian, double* m_yCartesian,unsigned int i);

		virtual double * extract_features(double* plainReading, unsigned int m_beams);
};

#endif // FE_CORNER_H
