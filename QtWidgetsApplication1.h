#pragma once
#ifdef WIN32  
#pragma execution_character_set("utf-8")
#endif
#ifndef QTWIDGET_H
#define QTWIDGET_H
#include <QtWidgets/QWidget>
#include "ui_QtWidgetsApplication1.h"
#include<qdebug.h>
#include<QFileDialog>
#include"ObjReader.h"
#include"obj_to_pcd.h"
#include<qstring.h>
#include"CloudReader.h"
//#include<QVTKWidget.h>
#include <vtkRenderWindow.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/visualization/pcl_visualizer.h>
#include<vector>
#include"myopengl.h"
using namespace pcl;

class QtWidgetsApplication1 : public QWidget
{
    Q_OBJECT

public:
    QtWidgetsApplication1(QWidget *parent = Q_NULLPTR);

public slots:
    void openObj();
    void ObjtoPcd();
    void savePcd();
    void openPcd();
    void close();
    void call();
    void getInfo();

public:
    pcl::PointCloud<pcl::PointNormal> cloud_out;
private:
    Ui::QtWidgetsApplication1Class ui;
    //pcl::visualization::PCLVisualizer::Ptr viewer;
    std::string objpath, pcdpath;
    CloudReader cloudData;
    QTimer* pTimer;
};
#endif 