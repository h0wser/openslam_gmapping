#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <cmath>


class FeatureExtractor {
	public:
		FeatureExtractor();

		virtual ~FeatureExtractor();

		/* Delta theta is the angle between each beam in readings */
		virtual unsigned int extract_features(double* readings, double delta_theta, unsigned int size) = 0;

		void remove_from_scan(double* readings, int i);
};

#endif // FEATURE_EXTRACTOR_H
