#include "gmapping/feature_extraction/fe_line_segment.h"
#include <visualization_msgs/Marker.h>

#include <iostream>

FE_LineSegment::FE_LineSegment() 
{
}

FE_LineSegment::~FE_LineSegment() {

}

void FE_LineSegment::setupLineFeatures()
{
	m_line_feature = line_feature::LineFeature();

	// default params
	m_line_feature.set_least_threshold(0.04);
	m_line_feature.set_min_line_length(0.5);
	m_line_feature.set_predict_distance(0.1);
	m_line_feature.set_seed_line_points(6);
	m_line_feature.set_min_line_points(12);

	m_line_feature.set_angle_increment(m_angle_res); // all in radians now
	m_line_feature.set_angle_start(m_min_angle);

	std::vector<double> bearings, cos_bearings, sin_bearings;
	std::vector<unsigned int> index;
	unsigned int i = 0;
	for (double b = m_min_angle; b <= m_max_angle; b += m_angle_res)
	{
		bearings.push_back(b);
		cos_bearings.push_back(cos(b));
		sin_bearings.push_back(sin(b));
		index.push_back(i);
		i++;
	}
	
	m_line_feature.setCosSinData(bearings, cos_bearings, sin_bearings, index);
}

double * FE_LineSegment::extract_features(double* readings, unsigned int size) {
	std::vector<double> scanData(readings, readings+size);

	std::vector<line> lines = std::vector<line>();
	std::vector<gline> glines = std::vector<gline>();

	m_line_feature.setRangeData(scanData);
	m_line_feature.extractLines(lines, glines);

	visualization_msgs::Marker marker_points;

    marker_points.header.frame_id = "base_link";
    marker_points.header.stamp = ros::Time::now();
    marker_points.id = 0;
    marker_points.ns = "fe_line_segment";
    marker_points.type = visualization_msgs::Marker::LINE_LIST;
    marker_points.action = visualization_msgs::Marker::ADD;
    marker_points.lifetime = ros::Duration();
    marker_points.scale.x = 0.1;

	marker_points.pose.orientation.w = 1;
	marker_points.color.a = 1.0;
	marker_points.color.r = 1.0;

	for (int i = 0; i < glines.size(); i++) {
		geometry_msgs::Point p1;
		geometry_msgs::Point p2;

		p1.x = glines[i].x1;
		p1.y = glines[i].y1;

		p2.x = glines[i].x2;
		p2.y = glines[i].y2;

		marker_points.points.push_back(p1);
		marker_points.points.push_back(p2);
	}

    if (m_marker_publisher.getNumSubscribers() > 0) {
        m_marker_publisher.publish(marker_points);
    }

	// use these lines to change readings so only readings on extracted lines are included
}
