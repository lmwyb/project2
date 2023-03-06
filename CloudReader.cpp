#include "CloudReader.h"
std::vector<PointCloud> cloudData;

CloudReader::CloudReader()
{

}

CloudReader::~CloudReader()
{
}

void CloudReader::importPcd(QString pcdPath)
{
	//------------------------------------加载点云数据------------------------------------------------------------
	std::string s = pcdPath.toStdString();
	//创建一个 PointCloud<PointXYZ> boost 共享指针并初始化它。
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);//点云数据坐标

	//从磁盘加载 PointCloud 数据,并且判断是否
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(s, *cloud) == -1)//*打开点云文件
	{
		PCL_ERROR("Couldn't read file \n");
		qDebug() << "无法打开点云文件！" << endl;
	}
	//pcl::PCDReader reader;	//定义点云读取对象
	//if (reader.read("test_pcd.pcd", *cloud) < 0)
	//{
	//	PCL_ERROR("\a->点云文件不存在！\n");
	//	system("pause");
	//	
	//}

	//以上代码已经读取到了点云数据，可以通过指针名字cloud访问该数据。
	//遍历输出点云数据的坐标
	/*std::cout << "Loaded "
		<< cloud->width * cloud->height
		<< " data points from test_pcd.pcd with the following fields: "
		<< std::endl;
	for (size_t i = 0; i < cloud->points.size(); ++i)
		std::cout << "    " << cloud->points[i].x
		<< " " << cloud->points[i].y
		<< " " << cloud->points[i].z << std::endl;*/

	//------------------------------------传数据到OpenGL------------------------------------------------------------------
	for (size_t i = 0; i < cloud->points.size(); ++i) {
		PointCloud pointCloud;
		pointCloud.x = cloud->points[i].x;
		pointCloud.y = cloud->points[i].y;
		pointCloud.z = cloud->points[i].z;
		cloudData.push_back(pointCloud);
		//qDebug() << pointCloud.x << pointCloud.y << pointCloud.z << endl;

	}
	
	qDebug() << "cloud" << cloudData.size();// << " " << "normals" << normalsData.size() << endl;
}

