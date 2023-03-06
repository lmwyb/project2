#pragma once
#ifdef _MSC_VER
#pragma once
#endif
#ifndef MYOPENGL_H
#define MYOPENGL_H
#include <iostream>  
#include <QtWidgets/qopenglwidget.h>
#include<qobject.h>
#include<glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QtCore/qtimer.h>
#include<QtGui/qevent.h>

#include"ObjReader.h"
#include"CloudReader.h"
#include<freeglut.h>

extern int smaller;
extern QString kedu;

using namespace std;

class myopengl :public QOpenGLWidget
{
	Q_OBJECT
public:
	myopengl(QWidget* parent = 0);
	~myopengl();


	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
	void wheelEvent(QWheelEvent* event);

	void createlist();
	void Axis();
	void drawCloud();
	void drawCylinder();
	void setLightRes();
	void SetupRC();
	
private:
	GLfloat cameraSpeed;
	glm::mat4 modelview;
	glm::mat4 projection;
	glm::vec3 camerapos = glm::vec3(0.0f, 1.0f, 13.0f);
	glm::vec3 camerafront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f);

	QPoint prepoint;
	GLfloat xspeed;
	GLfloat yspeed;
	GLfloat xdiff;
	GLfloat ydiff;
	QTimer* pTimer;
	GLfloat speed;
	GLfloat yaw;
	GLfloat pitch;
	GLfloat ScalefX;
	GLfloat ScalefY;
	GLfloat ScalefZ;
	GLboolean ispressed;
	GLint viewport[4];

	

	GLuint showFaceList, showWireList;
	int showstate = 1;
	bool showFace = true;
	bool showWire = false;
	bool showFlatlines = false;
	//bool data = false;
	int currentfile = 1;
	
};
#endif 
