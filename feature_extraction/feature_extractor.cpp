#include "gmapping/feature_extraction/feature_extractor.h"

FeatureExtractor::FeatureExtractor() {

}

FeatureExtractor::~FeatureExtractor() {

}

void FeatureExtractor::remove_from_scan(double* readings, int i) {
	*(readings+i) = FP_NAN;
}
