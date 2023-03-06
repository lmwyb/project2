#include "QtWidgetsApplication1.h"

QtWidgetsApplication1::QtWidgetsApplication1(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    connect(ui.pushButton1, SIGNAL(clicked()), this, SLOT(openObj()));

   /* viewer.reset(new pcl::visualization::PCLVisualizer("viewer", false));
    ui.qvtkWidget->SetRenderWindow(viewer->getRenderWindow());
    viewer->setupInteractor(ui.qvtkWidget->GetInteractor(), ui.qvtkWidget->GetRenderWindow());
    ui.qvtkWidget->update();*/
    connect(ui.pushButton2, SIGNAL(clicked()), this, SLOT(ObjtoPcd()));

    connect(ui.pushButton3, SIGNAL(clicked()), this, SLOT(savePcd()));
    connect(ui.pushButton4, SIGNAL(clicked()), this, SLOT(openPcd()));
    connect(ui.pushButton5, SIGNAL(clicked()), this, SLOT(close()));

    pTimer = new QTimer(this); //����һ����ʱ��
    //����ʱ���ļ�ʱ�ź���updateGL()��
    connect(pTimer, SIGNAL(timeout()), this, SLOT(call()));
    pTimer->start(10);//��10msΪһ����ʱ����

    
        
}
void QtWidgetsApplication1::openObj()
{
    QString s = QFileDialog::getOpenFileName(this, "���ļ�", "G:/OBJ", "Files(*.obj)");
    qDebug() << s << endl;//�õ�obj�ļ�����·��
    qDebug() << "��ʼ��ȡOBJ����" << endl;
    objpath = s.toStdString();
    ObjReader objData;
    objData.readfile(objpath);
    //qDebug() << mesh.n_edges() << endl;
    qDebug() << "��ȡOBJ���ݽ���" << endl;
}

void QtWidgetsApplication1::ObjtoPcd()
{
    qDebug() << "ת����ʼ" << endl;
    generatePcd(objpath, cloud_out);

   
    //QString s = QFileDialog::getOpenFileName(this, "���ļ�", "G:/data", "Files(*.pcd)");
    //qDebug() << s << endl;//�õ�pcd�ļ�����·��
    //qDebug() << "��ʼ��ȡ��������" << endl;
    //myopengl2 cloudData;
    //pcdpath = s.toStdString();
    //cloudData.readfile(pcdpath);
    //qDebug() << "��ȡ�������ݽ���" << endl;

    ////����pcd�ļ�
    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPoints(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl::io::loadPCDFile("G:/data/test/test03.pcd", *cloudPoints);
    ////�Ƴ����ڵ���
    //viewer->removeAllPointClouds();
    ////��������
    ////���õ�����ɫ
    //pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloudPoints, 255, 255, 255);
    ////������ɫ��Ⱦ	
    //viewer->addPointCloud(cloudPoints, cloud_color, "cloud");
    ////���õ��ƴ�С
    //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
    //viewer->resetCamera();
    //ui.qvtkWidget->update();
    qDebug() << "ת������" << endl;
}

void QtWidgetsApplication1::savePcd()
{
    qDebug() << "��ʼ����pcd�ļ�" << endl;
    QString s = QFileDialog::getSaveFileName(this, "�����ļ�", "G:/data/test", "Files(*.pcd)");
    std::string pcdpath = s.toStdString();
    pcl::io::savePCDFileBinary(pcdpath, cloud_out);
    qDebug() << "�ɹ�����pcd�ļ�" << endl;
}

void QtWidgetsApplication1::openPcd()
{
    QString s = QFileDialog::getOpenFileName(this, "���ļ�", "G:/data/test", "Files(*.pcd)");
    qDebug() << s << endl;//�õ�pcd�ļ�����·��
    qDebug() << "��ʼ��ȡ��������" << endl;
    cloudData.importPcd(s);
    qDebug() << "��ȡ�������ݽ���" << endl;
}

void QtWidgetsApplication1::close()
{
    QWidget::close();
}

void QtWidgetsApplication1::call()
{
    getInfo();
}

void QtWidgetsApplication1::getInfo()
{
  /*  QString b = QString::number(smaller, 10, 5);
    QString s = b + "mm";*/
    ui.lineEdit->setText(kedu);
}
