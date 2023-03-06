#pragma once
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/vtk_lib_io.h>
#include <pcl/common/transforms.h>
#include <vtkVersion.h>
#include <vtkPLYReader.h>
#include <vtkOBJReader.h>
#include <vtkTriangle.h>
#include <vtkTriangleFilter.h>
#include <vtkPolyDataMapper.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
using namespace std;
void uniform_sampling(vtkSmartPointer<vtkPolyData> polydata, double density, bool calc_normal, pcl::PointCloud<pcl::PointNormal>& cloud_out);
void generatePcd(string filePath, pcl::PointCloud<pcl::PointNormal>& cloud_out);