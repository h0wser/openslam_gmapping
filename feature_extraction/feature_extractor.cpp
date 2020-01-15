#include "gmapping/feature_extraction/feature_extractor.h"
#include <math.h>

#include <visualization_msgs/Marker.h>

FeatureExtractor::FeatureExtractor()
{
	ros::NodeHandle handle;
	m_marker_publisher = handle.advertise<visualization_msgs::Marker>("visualization_marker", 10);
}

FeatureExtractor::~FeatureExtractor()
{
}

void FeatureExtractor::remove_from_scan(double* readings, int i) {
	*(readings+i) = FP_NAN;
}
