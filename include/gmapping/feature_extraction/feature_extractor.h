#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <cmath>


class FeatureExtractor {
	public:
		FeatureExtractor();



		virtual ~FeatureExtractor();
		virtual double * extract_features(double* readings, unsigned int size) = 0;
	
	private:

		void remove_from_scan(double* readings, int i);
};

#endif // FEATURE_EXTRACTOR_H
