#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H


class FeatureExtractor {
	public:
		FeatureExtractor();

		virtual ~FeatureExtractor();

		virtual unsigned int extract_features(double* readings, unsigned int size) = 0;
};

#endif // FEATURE_EXTRACTOR_H
