#ifndef FEATURE_EXTRACTOR_H
#define FEATURE_EXTRACTOR_H

#include <cmath>
#include <ros/ros.h>


class FeatureExtractor {
	public:
		FeatureExtractor();

		virtual ~FeatureExtractor();
		virtual double * extract_features(double* readings, unsigned int size) = 0;

	protected:
		void remove_from_scan(double* readings, int i);

		ros::Publisher m_marker_publisher;
};

#endif // FEATURE_EXTRACTOR_H
