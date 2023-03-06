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

    pTimer = new QTimer(this); //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    connect(pTimer, SIGNAL(timeout()), this, SLOT(call()));
    pTimer->start(10);//以10ms为一个计时周期

    
        
}
void QtWidgetsApplication1::openObj()
{
    QString s = QFileDialog::getOpenFileName(this, "打开文件", "G:/OBJ", "Files(*.obj)");
    qDebug() << s << endl;//得到obj文件所在路径
    qDebug() << "开始读取OBJ数据" << endl;
    objpath = s.toStdString();
    ObjReader objData;
    objData.readfile(objpath);
    //qDebug() << mesh.n_edges() << endl;
    qDebug() << "读取OBJ数据结束" << endl;
}

void QtWidgetsApplication1::ObjtoPcd()
{
    qDebug() << "转换开始" << endl;
    generatePcd(objpath, cloud_out);

   
    //QString s = QFileDialog::getOpenFileName(this, "打开文件", "G:/data", "Files(*.pcd)");
    //qDebug() << s << endl;//得到pcd文件所在路径
    //qDebug() << "开始读取点云数据" << endl;
    //myopengl2 cloudData;
    //pcdpath = s.toStdString();
    //cloudData.readfile(pcdpath);
    //qDebug() << "读取点云数据结束" << endl;

    ////加载pcd文件
    //pcl::PointCloud<pcl::PointXYZ>::Ptr cloudPoints(new pcl::PointCloud<pcl::PointXYZ>);
    //pcl::io::loadPCDFile("G:/data/test/test03.pcd", *cloudPoints);
    ////移除窗口点云
    //viewer->removeAllPointClouds();
    ////点云设置
    ////设置点云颜色
    //pcl::visualization::PointCloudColorHandlerCustom<pcl::PointXYZ> cloud_color(cloudPoints, 255, 255, 255);
    ////点云颜色渲染	
    //viewer->addPointCloud(cloudPoints, cloud_color, "cloud");
    ////设置点云大小
    //viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "cloud");
    //viewer->resetCamera();
    //ui.qvtkWidget->update();
    qDebug() << "转换结束" << endl;
}

void QtWidgetsApplication1::savePcd()
{
    qDebug() << "开始保存pcd文件" << endl;
    QString s = QFileDialog::getSaveFileName(this, "保存文件", "G:/data/test", "Files(*.pcd)");
    std::string pcdpath = s.toStdString();
    pcl::io::savePCDFileBinary(pcdpath, cloud_out);
    qDebug() << "成功保存pcd文件" << endl;
}

void QtWidgetsApplication1::openPcd()
{
    QString s = QFileDialog::getOpenFileName(this, "打开文件", "G:/data/test", "Files(*.pcd)");
    qDebug() << s << endl;//得到pcd文件所在路径
    qDebug() << "开始读取点云数据" << endl;
    cloudData.importPcd(s);
    qDebug() << "读取点云数据结束" << endl;
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
