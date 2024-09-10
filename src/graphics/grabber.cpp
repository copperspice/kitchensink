/***********************************************************************
*
* Copyright (c) 2012-2024 Barbara Geller
* Copyright (c) 2012-2024 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "glwidget.h"
#include "grabber.h"

#include <QAction>
#include <QApplication>
#include <QGridLayout>
#include <QImage>
#include <QInputDialog>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPixmap>
#include <QRegularExpression>
#include <QScrollArea>
#include <QSlider>

Grabber::Grabber(QWidget *parent)
   : QMainWindow(parent)
{
   centralWidget = new QWidget(this);
   setCentralWidget(centralWidget);

   setWindowTitle("Grabber");

   glWidget    = new GLWidget;
   pixmapLabel = new QLabel;

   glWidgetArea = new QScrollArea;
   glWidgetArea->setWidget(glWidget);
   glWidgetArea->setWidgetResizable(true);
   glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
   glWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   glWidgetArea->setMinimumSize(50, 50);

   pixmapLabelArea = new QScrollArea;
   pixmapLabelArea->setWidget(pixmapLabel);
   pixmapLabelArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   pixmapLabelArea->setMinimumSize(50, 50);

   xSlider = createSlider("xRotationChanged(int)", "setXRotation(int)");
   ySlider = createSlider("yRotationChanged(int)", "setYRotation(int)");
   zSlider = createSlider("zRotationChanged(int)", "setZRotation(int)");

   createActions();
   createMenus();

   QGridLayout *centralLayout = new QGridLayout;

   centralLayout->addWidget(glWidgetArea, 0, 0);
   centralLayout->addWidget(pixmapLabelArea, 0, 1);
   centralLayout->addWidget(xSlider, 1, 0, 1, 2);
   centralLayout->addWidget(ySlider, 2, 0, 1, 2);
   centralLayout->addWidget(zSlider, 3, 0, 1, 2);

   centralWidget->setLayout(centralLayout);

   xSlider->setValue(15 * 16);
   ySlider->setValue(345 * 16);
   zSlider->setValue(0 * 16);
}

void Grabber::actionClose()
{
   this->parentWidget()->close();
}

void Grabber::about()
{
   QMessageBox::about(this, tr("About Grabber"),
         tr("The <b>Grabber</b> example demonstrates two approaches for rendering OpenGL into a pixmap."));
}

void Grabber::clearPixmap()
{
   setPixmap(QPixmap());
}

void Grabber::createActions()
{
   renderIntoPixmapAct = new QAction(tr("&Render into Pixmap..."), this);
   renderIntoPixmapAct->setShortcut(tr("Ctrl+R"));
   connect(renderIntoPixmapAct, &QAction::triggered, this, &Grabber::renderIntoPixmap);

   grabFrameBufferAct = new QAction(tr("&Grab Frame Buffer"), this);
   grabFrameBufferAct->setShortcut(tr("Ctrl+G"));
   connect(grabFrameBufferAct, &QAction::triggered, this, &Grabber::grabFrameBuffer);

   clearPixmapAct = new QAction(tr("&Clear Pixmap"), this);
   clearPixmapAct->setShortcut(tr("Ctrl+L"));
   connect(clearPixmapAct, &QAction::triggered, this, &Grabber::clearPixmap);

   exitAct = new QAction(tr("Close"), this);
   exitAct->setShortcuts(QKeySequence::Quit);
   connect(exitAct, &QAction::triggered, this, &Grabber::actionClose);

   aboutGrabber = new QAction(tr("&About"), this);
   connect(aboutGrabber, &QAction::triggered, this, &Grabber::about);

   aboutGrabber_Cs = new QAction(tr("About &CopperSpice"), this);
   connect(aboutGrabber_Cs, &QAction::triggered, qApp, &QApplication::aboutCs);
}

void Grabber::createMenus()
{
   fileMenu = menuBar()->addMenu(tr("&File"));
   fileMenu->addAction(renderIntoPixmapAct);
   fileMenu->addAction(grabFrameBufferAct);
   fileMenu->addAction(clearPixmapAct);
   fileMenu->addSeparator();
   fileMenu->addAction(exitAct);

   helpMenu = menuBar()->addMenu(tr("&Help"));
   helpMenu->addAction(aboutGrabber);
   helpMenu->addAction(aboutGrabber_Cs);
}

QSlider *Grabber::createSlider(const QString &changedSignal, const QString &adjustSlider)
{
   QSlider *slider = new QSlider(Qt::Horizontal);
   slider->setRange(0, 360 * 16);
   slider->setSingleStep(16);
   slider->setPageStep(15 * 16);
   slider->setTickInterval(15 * 16);
   slider->setTickPosition(QSlider::TicksRight);

   connect(slider, SIGNAL(valueChanged(int)), glWidget, adjustSlider);
   connect(glWidget, changedSignal, slider, SLOT(setValue(int)));

   return slider;
}

void Grabber::grabFrameBuffer()
{
   QImage image = glWidget->grabFramebuffer();
   image.setDevicePixelRatio(devicePixelRatioF());

   setPixmap(QPixmap::fromImage(image));
}

QSize Grabber::getSize()
{
   bool ok = false;

   QString text = QInputDialog::getText(this, tr("Grabber"), tr("Enter pixmap size:"),
         QLineEdit::Normal, tr("%1 x %2").formatArg(glWidget->width()).formatArg(glWidget->height()), &ok);

   if (! ok) {
      return QSize();
   }

   QRegularExpression regExp(tr("([0-9]+) *x *([0-9]+)"), QPatternOption::ExactMatchOption);
   QRegularExpressionMatch match = regExp.match(text);

   if (match.hasMatch()) {
      int width  = match.captured(1).toInteger<int>();
      int height = match.captured(2).toInteger<int>();

      if (width > 0 && width < 2048 && height > 0 && height < 2048) {
         return QSize(width, height);
      }
   }

   return glWidget->size();
}

void Grabber::renderIntoPixmap()
{
   QSize size = getSize();

   if (size.isValid()) {
      QPixmap pixmap = glWidget->renderPixmap(size.width(), size.height());
      setPixmap(pixmap);
   }
}

void Grabber::setPixmap(const QPixmap &pixmap)
{
   pixmapLabel->setPixmap(pixmap);
   QSize size = pixmap.size() / pixmap.devicePixelRatio();

   if (size - QSize(1, 0) == pixmapLabelArea->maximumViewportSize()) {
      size -= QSize(1, 0);
   }

   pixmapLabel->resize(size);
}

QSize Grabber::sizeHint() const
{
   return QSize(500, 400);
}
