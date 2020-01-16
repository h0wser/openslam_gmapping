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

void FeatureExtractor::set_min_angle(double m)
{
	m_min_angle = m;
}

void FeatureExtractor::set_max_angle(double m)
{
	m_max_angle = m;
}

void FeatureExtractor::set_angle_res(double r)
{
	m_angle_res = r;
}

double FeatureExtractor::get_min_angle() const
{
	return m_min_angle;
}

double FeatureExtractor::get_max_angle() const
{
	return m_max_angle;
}

double FeatureExtractor::get_angle_res() const
{
	return m_angle_res;
}

void FeatureExtractor::remove_from_scan(double* readings, int i) {
	*(readings+i) = FP_NAN;
}
