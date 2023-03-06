#include"ObjReader.h"
MyMesh mesh;
ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}
// 读取文件的函数
void ObjReader::readfile(string file)
{
    // 请求顶点法线 vertex normals
    mesh.request_vertex_normals();
    //如果不存在顶点法线，则报错 
    if (!mesh.has_vertex_normals())
    {
        cout << "错误：标准定点属性 “法线”不存在" << endl;
        return;
    }
    // 如果有顶点发现则读取文件，读入到mesh对象中
    OpenMesh::IO::Options opt;
    if (!OpenMesh::IO::read_mesh(mesh, file, opt))
    {
        cout << "无法读取文件:" << file << endl;
        return;
    }
    else {
        cout << "成功读取文件:" << file << endl;
        //createlist();
        //showFace = true;
        //data = true;
    }
    cout << endl; // 为了ui显示好看一些
                  //如果不存在顶点法线，则计算出
    if (!opt.check(OpenMesh::IO::Options::VertexNormal))
    {
        //cout << 222 << endl;
        // 通过面法线计算顶点法线
        mesh.request_face_normals();
        // mesh计算出顶点法线
        mesh.update_normals();
        // 释放面法线
        mesh.release_face_normals();
    }
}

