#include "gmapping/feature_extraction/fe_line_segment.h"

#include <stdio.h>

FE_LineSegment::FE_LineSegment() {

	double angle_min = -0.5;
	double angle_max = 0.5;
	double angle_increment = 0.25;

	m_line_feature = line_feature::LineFeature();
	m_line_feature.set_angle_increment(angle_increment); // degrees or radians?
	m_line_feature.set_angle_start(angle_min); // degrees or radians?

	std::vector<double> bearings, cos_bearings, sin_bearings;
	std::vector<unsigned int> index;
	unsigned int i = 0;
	for (double b = angle_min; b <= angle_max; b += angle_increment)
	{
		bearings.push_back(b);
		cos_bearings.push_back(cos(b));
		sin_bearings.push_back(sin(b));
		index.push_back(i);
		i++;
	}
	
	m_line_feature.setCosSinData(bearings, cos_bearings, sin_bearings, index);
}

FE_LineSegment::~FE_LineSegment() {

}

unsigned int FE_LineSegment::extract_features(double *readings, double delta_theta, unsigned int size) {
	std::vector<double> scanData(readings, readings+size);

	std::vector<line> lines = std::vector<line>();
	std::vector<gline> glines = std::vector<gline>();
	m_line_feature.extractLines(lines, glines);
}
