/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "glwidget.h"
#include "grabber.h"

#include <QtGui>
#include <QtOpenGL>

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

    // removed SIGNAL() to pass a string, removed SLOT() to pass a string
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

void Grabber::actionClose() {
   this->parentWidget()->close();
}

void Grabber::about()
{
    QMessageBox::about(this, tr("About Grabber"),
            tr("The <b>Grabber</b> example demonstrates two approaches for "
               "rendering OpenGL into a Qt pixmap."));
}

void Grabber::clearPixmap()
{
    setPixmap(QPixmap());
}

void Grabber::createActions()
{
    renderIntoPixmapAct = new QAction(tr("&Render into Pixmap..."), this);
    renderIntoPixmapAct->setShortcut(tr("Ctrl+R"));
    connect(renderIntoPixmapAct, SIGNAL(triggered()),
            this, SLOT(renderIntoPixmap()));

    grabFrameBufferAct = new QAction(tr("&Grab Frame Buffer"), this);
    grabFrameBufferAct->setShortcut(tr("Ctrl+G"));
    connect(grabFrameBufferAct, SIGNAL(triggered()),
            this, SLOT(grabFrameBuffer()));

    clearPixmapAct = new QAction(tr("&Clear Pixmap"), this);
    clearPixmapAct->setShortcut(tr("Ctrl+L"));
    connect(clearPixmapAct, SIGNAL(triggered()), this, SLOT(clearPixmap()));

    exitAct = new QAction(tr("Close"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(actionClose()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &CopperSpice"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
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
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

QSlider *Grabber::createSlider(const char *changedSignal,const char *setterSlot)
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    connect(slider, SIGNAL(valueChanged(int)), glWidget, setterSlot);
    connect(glWidget, changedSignal, slider, SLOT(setValue(int)));
    return slider;
}

void Grabber::grabFrameBuffer()
{
    QImage image = glWidget->grabFrameBuffer();
    setPixmap(QPixmap::fromImage(image));
}

QSize Grabber::getSize()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Grabber"),
                                         tr("Enter pixmap size:"),
                                         QLineEdit::Normal,
                                         tr("%1 x %2").arg(glWidget->width())
                                                      .arg(glWidget->height()),
                                         &ok);
    if (!ok)
        return QSize();

    QRegExp regExp(tr("([0-9]+) *x *([0-9]+)"));
    if (regExp.exactMatch(text)) {
        int width = regExp.cap(1).toInt();
        int height = regExp.cap(2).toInt();
        if (width > 0 && width < 2048 && height > 0 && height < 2048)
            return QSize(width, height);
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
    QSize size = pixmap.size();

    if (size - QSize(1, 0) == pixmapLabelArea->maximumViewportSize())
        size -= QSize(1, 0);

    pixmapLabel->resize(size);
}

QSize Grabber::sizeHint() const
{
   return QSize(500,400);
}


