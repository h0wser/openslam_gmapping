#include "laser_line_extraction/line_extraction_ros.h"
#include <cmath>
//#include <ros/console.h>

const double angle_max = 2.35619449;
const double angle_min = -2.35619449;
const double angle_increment=0.00436332313;

namespace line_extraction
{

///////////////////////////////////////////////////////////////////////////////
// Constructor / destructor
///////////////////////////////////////////////////////////////////////////////
LineExtractionROS::LineExtractionROS():
 // nh_(nh),
  //nh_local_(nh_local),
  data_cached_(false)
{
  //data_cached_ = false;
 // loadParameters();
  //line_publisher_ = nh_.advertise<laser_line_extraction::LineSegmentList>("line_segments", 1);
  //scan_subscriber_ = nh_.subscribe(scan_topic_, 1, &LineExtractionROS::laserScanCallback, this);
  //if (pub_markers_)
  //{
  //  marker_publisher_ = nh_.advertise<visualization_msgs::Marker>("line_markers", 1);
  //}
}

LineExtractionROS::~LineExtractionROS()
{
}

///////////////////////////////////////////////////////////////////////////////
// Run
///////////////////////////////////////////////////////////////////////////////
std::vector<Line> LineExtractionROS::run()
{
  // Extract the lines
  std::vector<Line> lines;
  line_extraction_.extractLines(lines);

  // Populate message
  //laser_line_extraction::LineSegmentList msg;
  //populateLineSegListMsg(lines, msg);
  
  // Publish the lines
  //line_publisher_.publish(msg);

  // Also publish markers if parameter publish_markers is set to true
  //if (pub_markers_)
  //{
  //  visualization_msgs::Marker marker_msg;
  //  populateMarkerMsg(lines, marker_msg);
  //  marker_publisher_.publish(marker_msg);
  //}
  return lines;
}

///////////////////////////////////////////////////////////////////////////////
// Load ROS parameters
///////////////////////////////////////////////////////////////////////////////
void LineExtractionROS::loadParameters()
{
  
  //ROS_DEBUG("*************************************");
  //ROS_DEBUG("PARAMETERS:");

  // Parameters used by this node
  
  //std::string frame_id, scan_topic;
  //bool pub_markers;

  //nh_local_.param<std::string>("frame_id", frame_id, "laser");
  //frame_id_ = frame_id;
  //ROS_DEBUG("frame_id: %s", frame_id_.c_str());

  //nh_local_.param<std::string>("scan_topic", scan_topic, "scan");
  //scan_topic_ = scan_topic;
  //ROS_DEBUG("scan_topic: %s", scan_topic_.c_str());

  //nh_local_.param<bool>("publish_markers", pub_markers, false);
  //pub_markers_ = pub_markers;
  //ROS_DEBUG("publish_markers: %s", pub_markers ? "true" : "false");

  // Parameters used by the line extraction algorithm

  double bearing_std_dev, range_std_dev, least_sq_angle_thresh, least_sq_radius_thresh,
         max_line_gap, min_line_length, min_range, min_split_dist, outlier_dist;
  int min_line_points;

  //nh_local_.param<double>("bearing_std_dev", bearing_std_dev, 1e-3);
  line_extraction_.setBearingVariance(1e-3);
  //ROS_DEBUG("bearing_std_dev: %f", bearing_std_dev);

  //nh_local_.param<double>("range_std_dev", range_std_dev, 0.02);
  line_extraction_.setRangeVariance(0.02);
  //ROS_DEBUG("range_std_dev: %f", range_std_dev);

  //nh_local_.param<double>("least_sq_angle_thresh", least_sq_angle_thresh, 1e-4);
  line_extraction_.setLeastSqAngleThresh(1e-4);
  //ROS_DEBUG("least_sq_angle_thresh: %f", least_sq_angle_thresh);
  
  //nh_local_.param<double>("least_sq_radius_thresh", least_sq_radius_thresh, 1e-4);
  line_extraction_.setLeastSqRadiusThresh(1e-4);
  //ROS_DEBUG("least_sq_radius_thresh: %f", least_sq_radius_thresh);

  //nh_local_.param<double>("max_line_gap", max_line_gap, 0.4);
  line_extraction_.setMaxLineGap(0.4);
  //ROS_DEBUG("max_line_gap: %f", max_line_gap);

  //nh_local_.param<double>("min_line_length", min_line_length, 0.5);
  line_extraction_.setMinLineLength(0.5);
  //ROS_DEBUG("min_line_length: %f", min_line_length);

  //nh_local_.param<double>("min_range", min_range, 0.4);
  line_extraction_.setMinRange(0.4);
  //ROS_DEBUG("min_range: %f", min_range);

  //nh_local_.param<double>("min_split_dist", min_split_dist, 0.05);
  line_extraction_.setMinSplitDist(0.05);
  //ROS_DEBUG("min_split_dist: %f", min_split_dist);

 // nh_local_.param<double>("outlier_dist", outlier_dist, 0.05);
  line_extraction_.setOutlierDist(0.05);
  //ROS_DEBUG("outlier_dist: %f", outlier_dist);

  //nh_local_.param<int>("min_line_points", min_line_points, 9);
  line_extraction_.setMinLinePoints(static_cast<unsigned int>(9));
  //ROS_DEBUG("min_line_points: %d", min_line_points);

 // ROS_DEBUG("*************************************");
}

///////////////////////////////////////////////////////////////////////////////
// Populate messages
///////////////////////////////////////////////////////////////////////////////
/*void LineExtractionROS::populateLineSegListMsg(const std::vector<Line> &lines,
                                                laser_line_extraction::LineSegmentList &line_list_msg)
{
  for (std::vector<Line>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit)
  {
    laser_line_extraction::LineSegment line_msg;
    line_msg.angle = cit->getAngle(); 
    line_msg.radius = cit->getRadius(); 
    line_msg.covariance = cit->getCovariance(); 
    line_msg.start = cit->getStart(); 
    line_msg.end = cit->getEnd(); 
    line_list_msg.line_segments.push_back(line_msg);
  }
  line_list_msg.header.frame_id = frame_id_;
  line_list_msg.header.stamp = ros::Time::now();
}*/

/*void LineExtractionROS::populateMarkerMsg(const std::vector<Line> &lines, 
                                           visualization_msgs::Marker &marker_msg)
{
  marker_msg.ns = "line_extraction";
  marker_msg.id = 0;
  marker_msg.type = visualization_msgs::Marker::LINE_LIST;
  marker_msg.scale.x = 0.1;
  marker_msg.color.r = 1.0;
  marker_msg.color.g = 0.0;
  marker_msg.color.b = 0.0;
  marker_msg.color.a = 1.0;
  for (std::vector<Line>::const_iterator cit = lines.begin(); cit != lines.end(); ++cit)
  {
    geometry_msgs::Point p_start;
    p_start.x = cit->getStart()[0];
    p_start.y = cit->getStart()[1];
    p_start.z = 0;
    marker_msg.points.push_back(p_start);
    geometry_msgs::Point p_end;
    p_end.x = cit->getEnd()[0];
    p_end.y = cit->getEnd()[1];
    p_end.z = 0;
    marker_msg.points.push_back(p_end);
  }
  marker_msg.header.frame_id = frame_id_;
  marker_msg.header.stamp = ros::Time::now();
}*/

///////////////////////////////////////////////////////////////////////////////
// Cache data on first LaserScan message received
///////////////////////////////////////////////////////////////////////////////
void LineExtractionROS::cacheData()
{
  std::vector<double> bearings, cos_bearings, sin_bearings;
  std::vector<unsigned int> indices;
  const std::size_t num_measurements = std::ceil(
      (angle_max - angle_min) / angle_increment);
  for (std::size_t i = 0; i < num_measurements; ++i)
  {
    const double b = angle_min + i * angle_increment;// different from us?
    bearings.push_back(b);
    cos_bearings.push_back(cos(b));
    sin_bearings.push_back(sin(b));
    indices.push_back(i);
  }

  line_extraction_.setCachedData(bearings, cos_bearings, sin_bearings, indices);
  //ROS_DEBUG("Data has been cached.");
}

///////////////////////////////////////////////////////////////////////////////
// Main LaserScan callback
///////////////////////////////////////////////////////////////////////////////
double * LineExtractionROS::laserScanCallback(double * plainreading,unsigned int m_beams)
{
  data_cached_ = false;
  loadParameters();
  if (!data_cached_)
  {
    //cacheData(scan_msg); 
    cacheData();
    data_cached_ = true;
  }

  //std::vector<double> scan_ranges_doubles(scan_msg->ranges.begin(), scan_msg->ranges.end());
  std::vector<double> scan_ranges_doubles(plainreading, plainreading+m_beams);
  line_extraction_.setRangeData(scan_ranges_doubles);
  std::vector<Line> lines=run();
  double * res=new double[m_beams];

  for(unsigned int i=0; i<lines.size();i++){    
    res[i]= lines[i].getRadius();
  }
 // double * res= &lines.radius_;
  return res;
}

} // namespace line_extraction

