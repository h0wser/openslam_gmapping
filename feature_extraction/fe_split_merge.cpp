#include "gmapping/feature_extraction/fe_split_merge.h"

FE_SplitMerge::FE_SplitMerge() {

}

FE_SplitMerge::~FE_SplitMerge() {

}

double* FE_SplitMerge::extract_features(double* plainReading, unsigned int m_beams) {
	plainReading = m_line_extractor.laserScanCallback(plainReading, m_beams);
	return plainReading;
}

