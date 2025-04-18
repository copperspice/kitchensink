/***********************************************************************
*
* Copyright (c) 2012-2025 Barbara Geller
* Copyright (c) 2012-2025 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QPoint>

class GLWidget : public QOpenGLWidget
{
   CS_OBJECT(GLWidget)

 public:
   GLWidget(QWidget *parent = nullptr);
   ~GLWidget();

   int xRotation() const {
      return xRot;
   }

   int yRotation() const {
      return yRot;
   }

   int zRotation() const {
      return zRot;
   }

   QPixmap renderPixmap(int width, int height);

   CS_SLOT_1(Public, void setXRotation(int angle))
   CS_SLOT_2(setXRotation)

   CS_SLOT_1(Public, void setYRotation(int angle))
   CS_SLOT_2(setYRotation)

   CS_SLOT_1(Public, void setZRotation(int angle))
   CS_SLOT_2(setZRotation)

   CS_SIGNAL_1(Public, void xRotationChanged(int angle))
   CS_SIGNAL_2(xRotationChanged, angle)

   CS_SIGNAL_1(Public, void yRotationChanged(int angle))
   CS_SIGNAL_2(yRotationChanged, angle)

   CS_SIGNAL_1(Public, void zRotationChanged(int angle))
   CS_SIGNAL_2(zRotationChanged, angle)

 protected:
   void initializeGL() override;
   void paintGL() override;
   void mousePressEvent(QMouseEvent *event) override;
   void mouseMoveEvent(QMouseEvent *event) override;

 private:
   GLuint makeGear(const GLfloat *reflectance, GLdouble innerRadius,
         GLdouble outerRadius, GLdouble thickness, GLdouble toothSize, GLint toothCount);

   void drawGear(GLuint gear, GLdouble dx, GLdouble dy, GLdouble dz, GLdouble angle);
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
