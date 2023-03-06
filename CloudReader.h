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
#include <pcl/features/normal_3d_omp.h>//ʹ��OMP��Ҫ��ӵ�ͷ�ļ�
#include <pcl/visualization/pcl_visualizer.h>
#include <boost/thread/thread.hpp>
#include <pcl/filters/voxel_grid.h>           //�����������񻯵��˲���ͷ�ļ� 
#include <pcl/filters/filter.h>             //�˲����ͷ�ļ�
#include <pcl/filters/passthrough.h>
#include <pcl/filters/project_inliers.h>          //�˲������ͷ�ļ�
#include <pcl/filters/statistical_outlier_removal.h> //ͳ�Ʒ���ȥ����Ⱥ��
#include <pcl/filters/radius_outlier_removal.h> //ͳ�Ʒ���ȥ����Ⱥ��
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
