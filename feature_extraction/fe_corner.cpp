#include "gmapping/feature_extraction/fe_corner.h"
#include <stdio.h>
#include <math.h>
#include "gmapping/utils/point.h"
#include <visualization_msgs/Marker.h>


using namespace GMapping;


const double lowerBound = -0.3436;
const double upperBound = 0.3515;

FE_Corner::FE_Corner() 
{

}

FE_Corner::~FE_Corner() {

}

double * FE_Corner::extract_features(double* plainReading, unsigned int m_beams) {
	double * angleArray = new double[m_beams];
	double * m_xCartesian=new double[m_beams];
	double * m_yCartesian=new double[m_beams];
	point<double> cornerPos[m_beams];

	for(int i=0;i<m_beams;i++){
        angleArray[i]= m_min_angle + i * m_angle_res; //(540-i)*0.25;
    }
	FE_Corner::polarToCartesian(m_beams,plainReading,angleArray,m_xCartesian,m_yCartesian);

	for(unsigned int i=0;i<m_beams;i++){
		int corner=0;
		if(isnan(plainReading[i])==0){
			corner= FE_Corner::cornerCheck(m_xCartesian,m_yCartesian,i);
		}
		if(corner){
			cornerPos[i].x=plainReading[i];//x is p
			cornerPos[i].y=angleArray[i];//y is angle
			cornerPos[i+5].x=plainReading[i+5];
			cornerPos[i+5].y=angleArray[i+5];
			cornerPos[i+10].x=plainReading[i+10];
			cornerPos[i+10].y=angleArray[i+10];
		}
	}

    visualization_msgs::Marker marker_points;
    marker_points.header.frame_id = "base_link";
    marker_points.header.stamp = ros::Time::now();
    marker_points.id = 0;
    marker_points.ns = "fe_corner";
    marker_points.type = visualization_msgs::Marker::POINTS;
    marker_points.action = visualization_msgs::Marker::ADD;
    marker_points.lifetime = ros::Duration();
    marker_points.scale.x = 0.2;
    marker_points.scale.y = 0.2;

    marker_points.color.g = 1.0;
    marker_points.color.a = 1.0;
    marker_points.pose.orientation.w = 1.0;

	for (unsigned int i = 0; i < m_beams; i++) {
		if (cornerPos[i].x != plainReading[i] && cornerPos[i].y != angleArray[i]) {
			plainReading[i] = FP_NAN;
		} else {
            // add to visualization marker yao
            geometry_msgs::Point p;
            p.x = m_xCartesian[i];
            p.y = m_yCartesian[i];
            p.z = 0;
            marker_points.points.push_back(p);
        }
	}
	
	delete [] angleArray;
	delete [] m_xCartesian;
	delete [] m_yCartesian;


    if (m_marker_publisher.getNumSubscribers() > 0) {
        m_marker_publisher.publish(marker_points);
    }

	return plainReading;
}


void FE_Corner::polarToCartesian(unsigned int m_beam, double *plainReading, double *angleArray, double *m_xCartesian, double *m_yCartesian)
{
    for (unsigned int i = 0; i < m_beam; i++)
    {
        m_xCartesian[i] = plainReading[i] * cos(angleArray[i]);
        m_yCartesian[i] = plainReading[i] * sin(angleArray[i]);
    }
}

int FE_Corner::cornerCheck(double *m_xCartesian, double *m_yCartesian, unsigned int i)
{
    unsigned int startPoint = i;
    unsigned int midPoint = i + 5;
    unsigned int endPoint = startPoint + 10;

    double m_vecAX = m_xCartesian[midPoint] - m_xCartesian[startPoint];
    double m_vecAY = m_yCartesian[midPoint] - m_yCartesian[startPoint];
    double m_vecBX = m_xCartesian[midPoint] - m_xCartesian[endPoint];
    double m_vecBY = m_yCartesian[midPoint] - m_yCartesian[endPoint];

    double productValue = m_vecAX * m_vecBX + m_vecAY * m_vecBY;
    double vecAValue = sqrt(m_vecAX * m_vecAX + m_vecAY * m_vecAY);
    double vecBValue = sqrt(m_vecBX * m_vecBX + m_vecBY * m_vecBY);
    double cosValue = productValue / (vecAValue * vecBValue);

    if (-cosValue <= upperBound && -cosValue >= lowerBound)
    {
        midPoint = i + 6;
        m_vecAX = m_xCartesian[midPoint] - m_xCartesian[startPoint];
        m_vecAY = m_yCartesian[midPoint] - m_yCartesian[startPoint];
        m_vecBX = m_xCartesian[midPoint] - m_xCartesian[endPoint];
        m_vecBY = m_yCartesian[midPoint] - m_yCartesian[endPoint];

        productValue = m_vecAX * m_vecBX + m_vecAY * m_vecBY;
        vecAValue = sqrt(m_vecAX * m_vecAX + m_vecAY * m_vecAY);
        vecBValue = sqrt(m_vecBX * m_vecBX + m_vecBY * m_vecBY);
        cosValue = productValue / (vecAValue * vecBValue);
        if (-cosValue <= upperBound && -cosValue >= lowerBound)
        {
            return 1;
        }
        else{
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
