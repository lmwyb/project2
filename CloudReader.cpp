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
	//------------------------------------���ص�������------------------------------------------------------------
	std::string s = pcdPath.toStdString();
	//����һ�� PointCloud<PointXYZ> boost ����ָ�벢��ʼ������
	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);//������������

	//�Ӵ��̼��� PointCloud ����,�����ж��Ƿ�
	if (pcl::io::loadPCDFile<pcl::PointXYZ>(s, *cloud) == -1)//*�򿪵����ļ�
	{
		PCL_ERROR("Couldn't read file \n");
		qDebug() << "�޷��򿪵����ļ���" << endl;
	}
	//pcl::PCDReader reader;	//������ƶ�ȡ����
	//if (reader.read("test_pcd.pcd", *cloud) < 0)
	//{
	//	PCL_ERROR("\a->�����ļ������ڣ�\n");
	//	system("pause");
	//	
	//}

	//���ϴ����Ѿ���ȡ���˵������ݣ�����ͨ��ָ������cloud���ʸ����ݡ�
	//��������������ݵ�����
	/*std::cout << "Loaded "
		<< cloud->width * cloud->height
		<< " data points from test_pcd.pcd with the following fields: "
		<< std::endl;
	for (size_t i = 0; i < cloud->points.size(); ++i)
		std::cout << "    " << cloud->points[i].x
		<< " " << cloud->points[i].y
		<< " " << cloud->points[i].z << std::endl;*/

	//------------------------------------�����ݵ�OpenGL------------------------------------------------------------------
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

