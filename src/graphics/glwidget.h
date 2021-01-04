/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class QPoint;

class GLWidget : public QGLWidget
{
   CS_OBJECT(GLWidget)

   public:
      GLWidget(QWidget *parent = nullptr);
      ~GLWidget();

      int xRotation() const { return xRot; }
      int yRotation() const { return yRot; }
      int zRotation() const { return zRot; }

      CS_SLOT_1(Public, void setXRotation(int angle))
      CS_SLOT_2(setXRotation)

      CS_SLOT_1(Public, void setYRotation(int angle))
      CS_SLOT_2(setYRotation)

      CS_SLOT_1(Public, void setZRotation(int angle))
      CS_SLOT_2(setZRotation)

      CS_SIGNAL_1(Public, void xRotationChanged(int angle))
      CS_SIGNAL_2(xRotationChanged,angle)

      CS_SIGNAL_1(Public, void yRotationChanged(int angle))
      CS_SIGNAL_2(yRotationChanged,angle)

      CS_SIGNAL_1(Public, void zRotationChanged(int angle))
      CS_SIGNAL_2(zRotationChanged,angle)

   protected:
      void initializeGL();
      void paintGL();
      void resizeGL(int width, int height);
      void mousePressEvent(QMouseEvent *event);
      void mouseMoveEvent(QMouseEvent *event);

   private:
      GLuint makeGear(const GLfloat *reflectance, GLdouble innerRadius,
                    GLdouble outerRadius, GLdouble thickness,
                    GLdouble toothSize, GLint toothCount);

      void drawGear(GLuint gear, GLdouble dx, GLdouble dy, GLdouble dz,GLdouble angle);
      void normalizeAngle(int *angle);

      CS_SLOT_1(Private, void advanceGears())
      CS_SLOT_2(advanceGears)

      GLuint gear1;
      GLuint gear2;
      GLuint gear3;
      int xRot;
      int yRot;
      int zRot;
      int gear1Rot;

      QPoint lastPos;
};

#endif
