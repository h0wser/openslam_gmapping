#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <cmath>
#include <ros/ros.h>


class FeatureExtractor {
	public:
		FeatureExtractor();

		virtual ~FeatureExtractor();
		virtual double * extract_features(double* readings, unsigned int size) = 0;

		void set_min_angle(double m);
		void set_max_angle(double m);
		void set_angle_res(double r);

		double get_min_angle() const;
		double get_max_angle() const;
		double get_angle_res() const;

	protected:
		void remove_from_scan(double* readings, int i);

		ros::Publisher m_marker_publisher;

		double m_min_angle;
		double m_max_angle;
		double m_angle_res;
};

#endif // FEATURE_EXTRACTOR_H
