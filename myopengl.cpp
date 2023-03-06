#include "myopengl.h"
int smaller = 10000000;
QString kedu = "1cm";

myopengl::myopengl(QWidget* parent) :QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);//键盘焦点，鼠标单击触发键盘事件
    //setMouseTracking(true);
    pTimer = new QTimer(this); //创建一个定时器
    //将定时器的计时信号与updateGL()绑定
    connect(pTimer, SIGNAL(timeout()), this, SLOT(update()));
    pTimer->start(10);//以10ms为一个计时周期

      //变量初始化
    cameraSpeed = 0.5f;
    speed = 1.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    xspeed = 0.0f;
    yspeed = 0.0f;
    xdiff = 0.0f;
    ydiff = 0.0f;
    ispressed = false;
    ScalefX = 1;
    ScalefY = 1;
    ScalefZ = 1;
}

myopengl::~myopengl()
{
}

//设置OpenGL渲染环境，定义显示列表等。该函数只在第一次调用resizeGL()或paintGL()前被自动调用一次。
void myopengl::initializeGL()
{
    glClearColor(0.3, 0.3, 0.3, 1);
    //glEnable(GL_DEPTH_TEST);//允许深度测试 
    //glShadeModel(GL_FLAT);//设置阴影平滑模式 
    //glDepthRange(0.0, 1.0);//the range of z mapping
    //glDepthFunc(GL_LEQUAL);//设置深度测试类型 
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//进行透视校正

    //实用显示列表
    //glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(2.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST); //用来开启深度缓冲区的功能，启动后OPengl就可以跟踪Z轴上的像素，那么它只有在前面没有东西的情况下才会绘制这个像素，在绘制3d时，最好启用，视觉效果会比较真实
    //glEnable(GL_TEXTURE_2D);
        // ------------------- Lighting  
    //glEnable(GL_LIGHTING); // 如果enbale那么就使用当前的光照参数去推导顶点的颜色
    //glEnable(GL_LIGHT0); //第一个光源，而GL_LIGHT1表示第二个光源
                     // ------------------- Display List  
    //setLightRes();
    //SetupRC();//设置环境光
    
}
//渲染OpenGL场景。每当部件需要更新时都会调用该函数。
void myopengl::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //--------------------摄像机 -----------------------------------------------------
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLfloat x = GLfloat(viewport[2]) / GLfloat(viewport[3]);
    projection = glm::perspective(45.0f, x, 0.1f, 100.0f);
    glLoadMatrixf(value_ptr(projection));
    //------------------------------------------------------------------------------
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    modelview = glm::lookAt(camerapos, camerapos + camerafront, cameraup);
    glLoadMatrixf(glm::value_ptr(modelview));
    //-----------------------绘图代码-----------------------------------------------
    glRotated(xspeed, 0.0f, 1.0f, 0.0f);
    glRotated(yspeed, 1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(ScalefX, ScalefY, ScalefZ);
    Axis();
    //qDebug()<<mesh.n_edges() << endl;
    //drawCylinder();
    //cout << "画不画" << mesh.n_edges()<< endl;
    
    createlist();
    drawCloud();
    //if (showFace)
        //glCallList(1);
   /* if (showFlatlines) {
        glCallList(showFaceList);
        glCallList(showWireList);
    }
    if (showWire)
        glCallList(showWireList);*/

    //glutSwapBuffers(); //这是Opengl中用于实现双缓存技术的一个重要函数
    glPopMatrix();
    glFlush();//刷新
}
//设置OpenGL的视口、投影等。每次部件改变大小时都会自动调用该函数。
void myopengl::resizeGL(int w, int h)
{
    viewport[0] = 0;
    viewport[1] = 0;
    viewport[2] = w;
    viewport[3] = h;
    glViewport(0, 0, w, h);
}

void myopengl::mousePressEvent(QMouseEvent* event)
{
    /*ispressed = true;
    prepoint = event->pos();*/

    xdiff = event->pos().x() - xspeed;
    ydiff = -event->pos().y() + yspeed;
}
void myopengl::mouseMoveEvent(QMouseEvent* event)
{
    float dx = event->pos().x() - prepoint.x();
    float dy = event->pos().y() - prepoint.y();
    //xspeed += (double)dx / 60.0 / 3.0;//逆时针旋转速度增加
    //yspeed += (double)dy / 60.0 / 3.0;

    xspeed = event->pos().x() - xdiff;
    yspeed = event->pos().y() + ydiff;


    //float sensitivity = 0.05f;//灵敏度
    //dx *= sensitivity;//偏移量x*灵敏度
    //dy *= sensitivity;//偏移量y*灵敏度

    //yaw += dx;
    //pitch += dy;
    //if (pitch > 89.0f)
    //    pitch = 89.0f;
    //if (pitch < -89.0f)
    //    pitch = -89.0f;

    //glm::vec3 front;
    //front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //front.y = sin(glm::radians(pitch));
    //front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    //camerafront = glm::normalize(front);

    update();
}
void myopengl::mouseReleaseEvent(QMouseEvent* event)
{

}
void myopengl::keyPressEvent(QKeyEvent* event)
{
    ////右向量
    //cameraRight[0] = cameraFront[1] * cameraUp[2] - cameraFront[2] * cameraUp[1];
    //cameraRight[1] = cameraFront[2] * cameraUp[0] - cameraFront[0] * cameraUp[2];
    //cameraRight[2] = cameraFront[0] * cameraUp[1] - cameraFront[1] * cameraUp[0];
    ////标准化
    //normalizedRight[0] = cameraRight[0] / sqrt(pow(cameraRight[0], 2) + pow(cameraRight[1], 2) + pow(cameraRight[2], 2));
    //normalizedRight[1] = cameraRight[1] / sqrt(pow(cameraRight[0], 2) + pow(cameraRight[1], 2) + pow(cameraRight[2], 2));
    //normalizedRight[2] = cameraRight[2] / sqrt(pow(cameraRight[0], 2) + pow(cameraRight[1], 2) + pow(cameraRight[2], 2));
    if (event->key() == Qt::Key_A)
    {
        camerapos -= glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;

        /* cameraPos[0] -= normalizedRight[0] * speed;
         cameraPos[1] -= normalizedRight[1] * speed;
         cameraPos[2] -= normalizedRight[2] * speed;*/
    }
    else if (event->key() == Qt::Key_D)
    {
        camerapos += glm::normalize(glm::cross(camerafront, cameraup)) * cameraSpeed;

        /* cameraPos[0] += normalizedRight[0] * speed;
         cameraPos[1] += normalizedRight[1] * speed;
         cameraPos[2] += normalizedRight[2] * speed;*/
    }
    else if (event->key() == Qt::Key_W)
    {
        camerapos += cameraSpeed * cameraup;

        /*cameraPos[0] += cameraUp[0] * speed;
        cameraPos[1] += cameraUp[1] * speed;
        cameraPos[2] += cameraUp[2] * speed;*/
    }
    else if (event->key() == Qt::Key_S)
    {
        camerapos -= cameraSpeed * cameraup;

        /*cameraPos[0] -= cameraUp[0] * speed;
        cameraPos[1] -= cameraUp[1] * speed;
        cameraPos[2] -= cameraUp[2] * speed;*/
    }
    else if (event->key() == Qt::Key_Q) {
        xspeed += 10;
    }
    else if (event->key() == Qt::Key_Left) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        yaw -= 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);

        //front[0] = cos(pitch * PI / 180) * cos(yaw * PI / 180);
        //front[1] = sin(pitch * PI / 180);
        //front[2] = cos(pitch * PI / 180) * sin(yaw * PI / 180);
        ////标准化
        //cameraFront[0] = front[0] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[1] = front[1] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[2] = front[2] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
    }
    else if (event->key() == Qt::Key_Right) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        yaw += 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);

        //front[0] = cos(pitch * PI / 180) * cos(yaw * PI / 180);
        //front[1] = sin(pitch * PI / 180);
        //front[2] = cos(pitch * PI / 180) * sin(yaw * PI / 180);
        ////标准化
        //cameraFront[0] = front[0] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[1] = front[1] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[2] = front[2] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
    }
    else if (event->key() == Qt::Key_Up) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        pitch -= 1;
        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);

        //front[0] = cos(pitch * PI / 180) * cos(yaw * PI / 180);
        //front[1] = sin(pitch * PI / 180);
        //front[2] = cos(pitch * PI / 180) * sin(yaw * PI / 180);
        ////标准化
        //cameraFront[0] = front[0] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[1] = front[1] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[2] = front[2] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
    }
    else if (event->key() == Qt::Key_Down) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
        pitch += 1;

        glm::vec3 front;
        front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        front.y = sin(glm::radians(pitch));
        front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        camerafront = glm::normalize(front);

        //front[0] = cos(pitch * PI / 180) * cos(yaw * PI / 180);
        //front[1] = sin(pitch * PI / 180);
        //front[2] = cos(pitch * PI / 180) * sin(yaw * PI / 180);
        ////标准化
        //cameraFront[0] = front[0] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[1] = front[1] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
        //cameraFront[2] = front[2] / sqrt(pow(front[0], 2) + pow(front[1], 2) + pow(front[2], 2));
    }
    update();
}
void myopengl::wheelEvent(QWheelEvent* event)
{
    QString danwei;
    int shu;
    if (event->delta() > 0) {//前进、放大
        camerapos += cameraSpeed * camerafront;

        /*cameraPos[0] -= speed * cameraFront[0];
        cameraPos[1] -= speed * cameraFront[1];
        cameraPos[2] -= speed * cameraFront[2];*/
        //qDebug() << "11111" << endl;

        smaller = smaller / 2;
        
        if (smaller==10000000) {
            danwei = "cm";
            shu = smaller / 10000000;
        }else if (smaller < 10000000 && smaller>=1000000) 
        {
            danwei = "mm";
            shu = smaller / 1000000;
        }
        else if (smaller < 1000000 && smaller >= 1000) {
            danwei = "um";
            shu = smaller / 1000;
        }
        else if (smaller < 1000 && smaller >= 1) {
            danwei = "nm";
            shu = smaller;
        }
        
        QString b = QString::number(shu);
        kedu = b + danwei;
        
        qDebug() << kedu << endl;
    }
    else {//后退、缩小
        camerapos -= cameraSpeed * camerafront;

        /*cameraPos[0] += speed * cameraFront[0];
        cameraPos[1] += speed * cameraFront[1];
        cameraPos[2] += speed * cameraFront[2];*/

        smaller = smaller * 2;

        if (smaller == 10000000) {
            danwei = "cm";
            shu = smaller / 10000000;
        }
        else if (smaller < 10000000 && smaller >= 1000000)
        {
            danwei = "mm";
            shu = smaller / 1000000;
        }
        else if (smaller < 1000000 && smaller >= 1000) {
            danwei = "um";
            shu = smaller / 1000;
        }
        else if (smaller < 1000 && smaller >= 1) {
            danwei = "nm";
            shu = smaller;
        }

        QString b = QString::number(shu);
        kedu = b + danwei;

        qDebug() << kedu << endl;
    }
    //gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2],
    //    cameraPos[0] + cameraFront[0], cameraPos[1] + cameraFront[1], cameraPos[2] + cameraFront[2],
    //    cameraUp[0], cameraUp[1], cameraUp[2]);//摄像机位置、目标位置、上向量
    update();
}

void myopengl::createlist()
{
   /* showFaceList = glGenLists(1);
    showWireList = glGenLists(1);*/
    
    //// 绘制 wire 
    //glNewList(showWireList, GL_COMPILE);
    //glDisable(GL_LIGHTING);
    //glLineWidth(1.0f);
    //glColor3f(0.5f, 0.5f, 0.5f);//灰色
    //glBegin(GL_LINES);
    //for (MyMesh::HalfedgeIter he_it = mesh.halfedges_begin(); he_it != mesh.halfedges_end(); ++he_it) {
    //    //链接这个有向边的起点和终点
    //    glVertex3fv(mesh.point(mesh.from_vertex_handle(*he_it)).data());
    //    glVertex3fv(mesh.point(mesh.to_vertex_handle(*he_it)).data());
    //}
    //glEnd();
    //glEnable(GL_LIGHTING);
    //glEndList();
    
    // 绘制flat
    if (mesh.n_edges()!=0) {
        //cout << 1111111111111 << endl;
        if (!glIsList((GLuint)(1))) {
            glNewList(1, GL_COMPILE);
            for (MyMesh::FaceIter f_it = mesh.faces_begin(); f_it != mesh.faces_end(); ++f_it) {
                glBegin(GL_TRIANGLES);
                for (MyMesh::FaceVertexIter fv_it = mesh.fv_iter(*f_it); fv_it.is_valid(); ++fv_it) {
                    glNormal3fv(mesh.normal(*fv_it).data());
                    glVertex3fv(mesh.point(*fv_it).data());
                }
                glEnd();
            }
            glEndList();
        }
        glCallList(1);

    }
    
}
void myopengl::Axis()
{
    //画下x,y,z轴
    glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f); //画红色的x轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(10000.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f); //画绿色的y轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 10000.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f); //画蓝色的z轴
    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 10000.0f);
    glEnd();
    glFlush();

    //坐标轴刻度
    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画x轴上点
    glBegin(GL_POINTS);
    for (int x = 1; x < 1000; x = x + 1) {
        glVertex3f((float)x, 0.0f, 0.0f);
    }
    glEnd();

    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画y轴上点
    glBegin(GL_POINTS);
    for (int y = 1; y < 1000; y = y + 1) {
        glVertex3f(0.0f, (float)y, 0.0f);
    }
    glEnd();

    glPointSize(5.0f);
    glColor3f(1.0f, 1.0f, 1.0f);//画z轴上点
    glBegin(GL_POINTS);
    for (int z = 1; z < 1000; z = z + 1) {
        glVertex3f(0.0f, 0.0f, (float)z);
    }
    glEnd();
}
void myopengl::drawCloud() {
    //if (cloudData.size() != 0) {
        //if (!glIsList((GLuint)(2))) {
            //glNewList(2, GL_COMPILE);
            glPushMatrix();
            glColor3f(1, 0, 0);
            glPointSize(0.05);
            glBegin(GL_POINTS);
            for (int i = 0; i < cloudData.size(); i++) {
                //qDebug() << cloudData[i].x << cloudData[i].y << cloudData[i].z << endl;
                glVertex3d(cloudData[i].x, cloudData[i].y, cloudData[i].z);
            }
            glEnd();
            glPopMatrix();
           // glEndList();
        //}
        //glCallList(2);
   // }  
}
void myopengl::drawCylinder()
{
    // 侧面用多个四边形,底面用多个三角形来表示
    glBegin(GL_QUAD_STRIP);//连续填充四边形串
    int i = 0;
    for (i = 0; i <= 360; i += 15)
    {
        float p = i * 3.14 / 180;
        glVertex3f(sin(p), cos(p), 1.0f);
        glVertex3f(sin(p), cos(p), 0.0f);
    }
    glEnd();
}

void myopengl::setLightRes() {
    //GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    GLfloat lightPosition[] = { 0.0f, 1.0f, 0.0f, 0.0f }; // 平行光源, GL_POSITION属性的最后一个参数为0


    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}
void myopengl::SetupRC()
{
    glEnable(GL_DEPTH_TEST);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    // 启用光照计算
    glEnable(GL_LIGHTING);
    // 指定环境光强度（RGBA）
    GLfloat ambientLight[] = { 1.0f, 0.0f, 0.0f, 0.0f };
    // 设置光照模型，将ambientLight所指定的RGBA强度值应用到环境光
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    // 启用颜色追踪
    glEnable(GL_COLOR_MATERIAL);
    // 设置多边形正面的环境光和散射光材料属性，追踪glColor
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    //glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}


