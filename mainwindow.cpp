#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(moveFigure()));
        timer->start(5);
    setWindowState(Qt::WindowFullScreen);
}

GLint Width = 512, Height = 512;

/* размер куба */
const int CubeSize = 200;

void MainWindow::initializeGL()
{
    location1[0]=(width())/2;
    location1[1]=(height())/2;
    location2[0]=(width())/2;
    location2[1]=(height())/2;
    move1[0]=0;
    move1[1]=1;

    move2[0]=0;
    move2[1]=-1;

    rotate1=0.0;
    rotate2=0.0;
    //glEnable(GL_LIGHTING);
}

void MainWindow::resizeGL(int nWidth, int nHeight)
{
    Width = nWidth;
    Height = nHeight;

    /* устанавливаем размеры области отображения */
    glViewport(0, 0, nWidth, nHeight);

    /* ортографическая проекция */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, nWidth, 0, nHeight, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat lightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat lightPosition[]= { 0.0f, 0.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1,GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT1);
    glLoadIdentity();
}

void MainWindow::mouseMoveEvent(QMouseEvent *me){

}

void MainWindow::paintGL()
{
    recalculate();

    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    glTranslatef(location1[0],location1[1],0);
    glRotatef(rotate1,0.0f,0.0f,1.0f);
    glColor3ub(255,0,0);
    glBegin(GL_POLYGON);
    for (int i=0; i<sizeof(figure1)/sizeof(int[2]); i++){
        glVertex2f(figure1[i][0],figure1[i][1]);
    }
    glEnd();
    glColor3ub(0,255,0);
    glLoadIdentity();
    glTranslatef(location2[0],location2[1],0);
    glRotatef(rotate2,0.0f,0.0f,1.0f);
    glBegin(GL_POLYGON);
    for (int i=0; i<sizeof(figure2)/sizeof(int[2]); i++){
        glVertex2f(figure2[i][0],figure2[i][1]);
    }
    glEnd();

    glFinish();
}

void MainWindow::keyPressEvent(QKeyEvent *ke){
    if (ke->key()==Qt::Key_Escape){
        //setWindowState(Qt::WindowNoState);
        exit(0);
    }
    updateGL();
}

void MainWindow::mousePressEvent(QMouseEvent * me){
    glLoadIdentity();
    glDisable(GL_LIGHT1);
    GLfloat lightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat x=me->x()/(float)width();
    GLfloat y=me->y()/(float)height();
    qDebug()<<"mouse click "<<x<< " " << y;
    GLfloat lightPosition[]= {me->x(), me->y(), 10, 1.0f };
    GLfloat lightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
    glLightfv(GL_LIGHT1,GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glEnable(GL_LIGHT1);
    glLoadIdentity();

}

void MainWindow::recalculate()
{
    if (location1[0]+move1[0]>width()-figure1width/2|| location1[0]<figure1width/2){
        move1[0]*=-1;
    }
    if (location1[1]+move1[1]>height()-figure1height/2|| location1[1]<figure1height/2){
        move1[1]*=-1;
    }
    if (location2[0]+move2[0]>width()-figure2width/2 || location2[0]<figure2width/2){
        move2[0]*=-1;
    }
    if (location2[1]+move2[1]>height()-figure2height/2|| location2[1]<figure2height/2){
        move2[1]*=-1;
    }
    location1[0]+=move1[0];
    location1[1]+=move1[1];
    location2[0]+=move2[0];
    location2[1]+=move2[1];

    rotate1+=0.05f;
    rotate2-=0.1f;

    figure1[0][0]=-figure1width/2;
    figure1[0][1]=-figure1height/2;
    figure1[1][0]=-figure1width/2;
    figure1[1][1]=figure1height/2;
    figure1[2][0]=figure1width/2;
    figure1[2][1]=figure1height/2;
    figure1[3][0]=figure1width/2;
    figure1[3][1]=-figure1height/2;

    figure2[0][0]=-figure2width/2;
    figure2[0][1]=-figure2height/2;
    figure2[1][0]=-figure2width/2;
    figure2[1][1]=figure2height/2;
    figure2[2][0]=figure2width/2;
    figure2[2][1]=figure2height/2;
    figure2[3][0]=figure2width/2;
    figure2[3][1]=-figure2height/2;
}

void MainWindow::moveFigure(){
    updateGL();
}
