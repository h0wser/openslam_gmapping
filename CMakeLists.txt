cmake_minimum_required(VERSION 2.8.3)
project(openslam_gmapping)

## Find catkin macros and libraries
find_package(catkin REQUIRED COMPONENTS roscpp)
find_package(Eigen3 REQUIRED COMPONENTS)

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
catkin_package(
  INCLUDE_DIRS include ${EIGEN3_INCLUDE_DIRS}
  LIBRARIES utils sensor_base sensor_odometry sensor_range log configfile scanmatcher feature_extraction gridfastslam 
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(include ${EIGEN3_INCLUDE_DIRS} ${catkin_INCLUDE_DIRS})
include_directories(include)

#SUBDIRS=utils sensor log configfile scanmatcher gridfastslam gui

# utils/
# OBJS= stat.o  movement.o
# APPS= autoptr_test #stat_test
# CPPFLAGS+= -DFSLINE
add_library(utils
  utils/stat.cpp
  utils/movement.cpp)
add_executable(autoptr_test
  utils/autoptr_test.cpp)

# sensor/
# SUBDIRS=sensor_base sensor_odometry sensor_range

# sensor/sensor_base/
# OBJS= sensor.o sensorreading.o
add_library(sensor_base
  sensor/sensor_base/sensor.cpp
  sensor/sensor_base/sensorreading.cpp)

# sensor/sensor_odometry/
# LDFLAGS+= -lsensor_base
# OBJS= odometrysensor.o odometryreading.o
add_library(sensor_odometry
  sensor/sensor_odometry/odometrysensor.cpp
  sensor/sensor_odometry/odometryreading.cpp)
target_link_libraries(sensor_odometry
  sensor_base)

# sensor/sensor_range/
# CPPFLAGS+= -I../
# LDFLAGS+= -lsensor_base
# OBJS= rangesensor.o rangereading.o 
add_library(sensor_range
  sensor/sensor_range/rangesensor.cpp
  sensor/sensor_range/rangereading.cpp)
target_link_libraries(sensor_range
  sensor_base)

# log/
# CPPFLAGS+= -I../sensor
# OBJS= configuration.o carmenconfiguration.o sensorlog.o sensorstream.o
# APPS= log_test log_plot scanstudio2carmen rdk2carmen
# LDFLAGS+=  -lsensor_range -lsensor_odometry -lsensor_base 
add_library(log
  log/configuration.cpp
  log/carmenconfiguration.cpp
  log/sensorlog.cpp
  log/sensorstream.cpp)
add_executable(log_test
  log/log_test.cpp)
add_executable(log_plot
  log/log_plot.cpp)
add_executable(scanstudio2carmen
  log/scanstudio2carmen.cpp)
add_executable(rdk2carmen
  log/rdk2carmen.cpp)
target_link_libraries(log_test log)
target_link_libraries(log_plot log)
target_link_libraries(scanstudio2carmen log)
target_link_libraries(rdk2carmen log)
target_link_libraries(log
  sensor_range sensor_odometry sensor_base)

# configfile/
# OBJS= configfile.o 
# APPS= configfile_test 
add_library(configfile
  configfile/configfile.cpp)
add_executable(configfile_test
  configfile/configfile_test.cpp)
target_link_libraries(configfile_test configfile)

# scanmatcher/
# CPPFLAGS+=-I../sensor
# OBJS= smmap.o scanmatcher.o scanmatcherprocessor.o eig3.o
# APPS= scanmatch_test icptest
# LDFLAGS+= -llog -lsensor_range -lsensor_odometry -lsensor_base -lutils

# Options for enabling different types of feature extraction in scanmatcher
option(USE_CORNER "Use corner feature extraction" OFF)
option(USE_SPLIT_MERGE "Use split and merge feature extraction" OFF)
option(USE_LINE_SEGMENT "Use line segment feature extraction" OFF)


if (USE_CORNER)
	add_definitions(-DUSE_FE_CORNER)
endif()

if (USE_SPLIT_MERGE)
	add_definitions(-DUSE_FE_SPLIT_MERGE)
endif()

if (USE_LINE_SEGMENT)
	add_definitions(-DUSE_FE_LINE_SEGMENT)
endif()

add_library(scanmatcher
  scanmatcher/smmap.cpp
  scanmatcher/scanmatcher.cpp
  scanmatcher/scanmatcherprocessor.cpp
  scanmatcher/eig3.cpp)
add_executable(scanmatch_test
  scanmatcher/scanmatch_test.cpp)
add_executable(icptest
  scanmatcher/icptest.cpp)
target_link_libraries(scanmatch_test scanmatcher)
target_link_libraries(icptest scanmatcher)
target_link_libraries(scanmatcher
  log sensor_range sensor_odometry sensor_base utils feature_extraction)

# gridfastslam/
# CPPFLAGS+=-I../sensor
# OBJS= gridslamprocessor_tree.o motionmodel.o gridslamprocessor.o gfsreader.o
# APPS= gfs2log gfs2rec gfs2neff #gfs2stat
# LDFLAGS+=  -lscanmatcher -llog -lsensor_range -lsensor_odometry -lsensor_base -lutils
add_library(gridfastslam
  gridfastslam/gridslamprocessor_tree.cpp
  gridfastslam/motionmodel.cpp
  gridfastslam/gridslamprocessor.cpp
  gridfastslam/gfsreader.cpp)
add_executable(gfs2log
  gridfastslam/gfs2log.cpp)
add_executable(gfs2rec
  gridfastslam/gfs2rec.cpp)
add_executable(gfs2neff
  gridfastslam/gfs2neff.cpp)
target_link_libraries(gfs2log gridfastslam)
target_link_libraries(gfs2rec gridfastslam)
target_link_libraries(gfs2neff gridfastslam)
target_link_libraries(gridfastslam
  scanmatcher log sensor_range sensor_odometry sensor_base utils feature_extraction)



  add_library(line feature_extraction/line.cpp)
  target_link_libraries(line ${catkin_LIBRARIES})
  
  add_library(line_extraction feature_extraction/line_extraction.cpp)
  target_link_libraries(line_extraction ${catkin_LIBRARIES})
  
  add_library(line_extraction_ros feature_extraction/line_extraction_ros.cpp)
  target_link_libraries(line_extraction_ros line line_extraction ${catkin_LIBRARIES})
  add_dependencies(line_extraction_ros laser_line_extraction_generate_messages_cpp)

# feature_extraction/

add_library(feature_extraction
	feature_extraction/fe_line_segment.cpp
	feature_extraction/feature_extractor.cpp
	feature_extraction/line_feature.cpp
	feature_extraction/fe_corner.cpp
	feature_extraction/line_extraction_ros.cpp
	feature_extraction/line_extraction.cpp
	feature_extraction/line.cpp
	feature_extraction/fe_split_merge.cpp
  )
target_link_libraries(feature_extraction ${catkin_LIBRARIES})

  
#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
install(TARGETS utils autoptr_test sensor_base sensor_odometry sensor_range sensor_range log log_test log_plot scanstudio2carmen rdk2carmen configfile configfile_test scanmatcher scanmatch_test icptest gridfastslam gfs2log gfs2rec gfs2neff line_extraction_ros line_extraction line
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark cpp header files for installation
install(DIRECTORY include/gmapping
  DESTINATION ${CATKIN_GLOBAL_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h*"
  PATTERN ".svn" EXCLUDE
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_openslam_gmapping.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
