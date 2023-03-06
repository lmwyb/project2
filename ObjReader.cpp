#include"ObjReader.h"
MyMesh mesh;
ObjReader::ObjReader()
{
}

ObjReader::~ObjReader()
{
}
// ��ȡ�ļ��ĺ���
void ObjReader::readfile(string file)
{
    // ���󶥵㷨�� vertex normals
    mesh.request_vertex_normals();
    //��������ڶ��㷨�ߣ��򱨴� 
    if (!mesh.has_vertex_normals())
    {
        cout << "���󣺱�׼�������� �����ߡ�������" << endl;
        return;
    }
    // ����ж��㷢�����ȡ�ļ������뵽mesh������
    OpenMesh::IO::Options opt;
    if (!OpenMesh::IO::read_mesh(mesh, file, opt))
    {
        cout << "�޷���ȡ�ļ�:" << file << endl;
        return;
    }
    else {
        cout << "�ɹ���ȡ�ļ�:" << file << endl;
        //createlist();
        //showFace = true;
        //data = true;
    }
    cout << endl; // Ϊ��ui��ʾ�ÿ�һЩ
                  //��������ڶ��㷨�ߣ�������
    if (!opt.check(OpenMesh::IO::Options::VertexNormal))
    {
        //cout << 222 << endl;
        // ͨ���淨�߼��㶥�㷨��
        mesh.request_face_normals();
        // mesh��������㷨��
        mesh.update_normals();
        // �ͷ��淨��
        mesh.release_face_normals();
    }
}

