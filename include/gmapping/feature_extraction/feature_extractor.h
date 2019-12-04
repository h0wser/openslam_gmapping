#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H


class FeatureExtractor {
	public:
		FeatureExtractor();

		virtual ~FeatureExtractor();

		/* Delta theta is the angle between each beam in readings */
		virtual unsigned int extract_features(double* readings, double delta_theta, unsigned int size) = 0;
};

#endif // FEATURE_EXTRACTOR_H
