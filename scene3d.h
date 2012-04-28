#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>

class Scene3D : public QGLWidget
{
   private:
      GLfloat xRot;
      GLfloat yRot;
      GLfloat zRot;
      GLfloat zTra;
      GLfloat nSca;

      QPoint ptrMousePosition;

      void scale_plus();
      void scale_minus();
      void rotate_up();
      void rotate_down();
      void rotate_left();
      void rotate_right();
      void translate_down();
      void translate_up();
      void defaultScene();

      void drawAxis();

      void getVertexArray();
      void getColorArray();
      void getIndexArray();
      void drawFigure();

   protected:
      void initializeGL();
      void resizeGL(int nWidth, int nHeight);
      void paintGL();
      void mousePressEvent(QMouseEvent* pe);
      void mouseMoveEvent(QMouseEvent* pe);
      void mouseReleaseEvent(QMouseEvent* pe);
      void wheelEvent(QWheelEvent* pe);
      void keyPressEvent(QKeyEvent* pe);

   public:
      Scene3D(QWidget* parent = 0);
};
#endif
