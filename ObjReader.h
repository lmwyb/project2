#pragma once
#include <iostream>  
#include <OpenMesh/Core/IO/MeshIO.hh>  
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>  

typedef OpenMesh::TriMesh_ArrayKernelT<> MyMesh;

extern MyMesh mesh;
using namespace std;
class ObjReader
{
public:
	ObjReader();
	~ObjReader();

public:
	void readfile(string file);
};




