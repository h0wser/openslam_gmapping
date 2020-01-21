#include "gmapping/feature_extraction/fe_split_merge.h"

FE_SplitMerge::FE_SplitMerge() 
{

}

FE_SplitMerge::~FE_SplitMerge() {

}

double* FE_SplitMerge::extract_features(double* plainReading, unsigned int m_beams) {
	m_line_extractor.setMinAngle(m_min_angle);
	m_line_extractor.setMaxAngle(m_max_angle);
	m_line_extractor.setAngleRes(m_angle_res);

	plainReading = m_line_extractor.laserScanCallback(plainReading, m_beams);
	return plainReading;
}

