/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (c) 2006-2012 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* * Redistributions of source code must retain the above copyright notice,
*   this list of conditions and the following disclaimer.
*
* * Redistributions in binary form must reproduce the above copyright
*   notice, this list of conditions and the following disclaimer in the
*   documentation and/or other materials provided with the distribution.
*
* * Neither the name of the Nokia Corporation nor the names of its
*   contributors may be used to endorse or promote products derived from
*   this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
***********************************************************************/

#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
    CS_OBJECT(GLWidget)

public:
    GLWidget(QWidget *parent = 0);
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

private :
    CS_SLOT_1(Private, void advanceGears())
    CS_SLOT_2(advanceGears) 

    GLuint makeGear(const GLfloat *reflectance, GLdouble innerRadius,
                    GLdouble outerRadius, GLdouble thickness,
                    GLdouble toothSize, GLint toothCount);

    void drawGear(GLuint gear, GLdouble dx, GLdouble dy, GLdouble dz,GLdouble angle);
    void normalizeAngle(int *angle);

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
