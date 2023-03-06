#pragma once
#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")
#endif
#include<iostream>
#include<fstream>
#include<iomanip>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<qdebug.h>
#include <pcl/kdtree/kdtree_flann.h>
//#include <pcl/features/normal_3d.h>
#include <pcl/features/normal_3d_omp.h>//使用OMP需要添加的头文件
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/filters/voxel_grid.h>           //用于体素网格化的滤波类头文件 
#include <pcl/filters/filter.h>             //滤波相关头文件
#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>          //滤波相关类头文件
#include <pcl/filters/statistical_outlier_removal.h> //统计方法去除离群点
#include <pcl/filters/radius_outlier_removal.h> //统计方法去除离群点
#include <pcl/filters/approximate_voxel_grid.h>  //ApproximateVoxelGrid 

using namespace std;
struct PointCloud
{
	double x;
	double y;
	double z;
};
extern std::vector<PointCloud> cloudData;

class CloudReader
{
public:
	CloudReader();
	~CloudReader();

	void importPcd(QString pcdPath);
	
private:

};
