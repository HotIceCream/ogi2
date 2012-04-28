#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGLWidget>
#include <QtOpenGL>
#include <QTimer>

class MainWindow : public QGLWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);


    void initializeGL();
    void resizeGL(int nWidth, int nHeight);
    void paintGL();

    void recalculate();
    void mousePressEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *ke);

    void mouseMoveEvent(QMouseEvent *me);
private:
    static int const figure1width=200;
    static int const figure1height=200;
    static int const figure2width=150;
    static int const figure2height=150;
    int location1[2];
    int location2[2];
    int figure1[4][2];
    int figure2[4][2];
    int move1[2];
    int move2[2];

    GLfloat rotate1;
    GLfloat rotate2;
private slots:
    void moveFigure();
};
#endif // MAINWINDOW_H
