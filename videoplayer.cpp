/**********************************************************************
*
* Copyright (c) 2012-2013 Barbara Geller
* Copyright (c) 2011-2012 Nokia Corporation and/or its subsidiary(-ies).
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

#include "util.h"
#include "videoplayer.h"
#include "videowidget.h"

#include <QGroupBox>
#include <QtMultimedia>

VideoPlayer::VideoPlayer(QWidget *parent)
   : QWidget(parent), m_surface(0)
{
   setWindowTitle(tr("Video Widget"));

   //
   QGroupBox *groupBox = new QGroupBox(tr("Send Email"));
   QFont font = groupBox->font();
   font.setPointSize(10);
   groupBox->setFont(font);

   QLabel *labelTo = new QLabel(tr("To:"));
   labelTo->setFont(font);

   QLineEdit *e_to = new QLineEdit();
   e_to->setFont(font);

   QLabel *labelSubject = new QLabel(tr("Subject:"));
   labelSubject->setFont(font);

   QLineEdit *e_subject = new QLineEdit();
   e_subject->setFont(font);

   QLabel *labelBody = new QLabel(tr("Body:"));
   labelBody->setFont(font);

   QTextEdit *e_body = new QTextEdit();
   e_body->setFont(font);

   //
   QPushButton *close_PB  = new QPushButton(tr("Close"));
   close_PB->setFont(font);

   //
   VideoWidget *videoWidget = new VideoWidget;     
   m_surface = videoWidget->videoSurface();

   QGridLayout *gLayout = new QGridLayout;
   gLayout->addWidget(labelTo,0,0);
   gLayout->addWidget(e_to,0,1);
   gLayout->addWidget(labelSubject,1,0);
   gLayout->addWidget(e_subject,1,1);
   gLayout->addWidget(labelBody, 2, 0);
   gLayout->addWidget(e_body, 2, 1, 1, 2);
   gLayout->addWidget(videoWidget, 0, 2, 2, 1);
   groupBox->setLayout(gLayout);

   QHBoxLayout *bottomLayout2 = new QHBoxLayout;
   bottomLayout2->addStretch();
   bottomLayout2->addWidget(close_PB);
   bottomLayout2->addStretch();

   QBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(groupBox);
   mainLayout->addSpacing(8);
   mainLayout->addLayout(bottomLayout2);

   mainLayout->setContentsMargins(14,14,14,9);
   setLayout(mainLayout);

   // load data from resource file
   QString fileName = ":/resources/email_3.gif";

   if (! fileName.isEmpty()) {
      m_surface->stop();

      m_movie.setFileName(fileName);

      if (! m_movie.isValid()) {
         ksMsg("Image is invalid and will not be displayed.");
      }

      m_movie.jumpToFrame(0);
      m_movie.start();

   }

   // signals
   connect(&m_movie, SIGNAL(stateChanged(QMovie::MovieState)), this, SLOT(stateChanged(QMovie::MovieState)));
   connect(&m_movie, SIGNAL(frameChanged(int)), this, SLOT(frameChanged(int)));        
   connect(close_PB, SIGNAL(clicked()), this, SLOT(actionClose()));
}

VideoPlayer::~VideoPlayer()
{
}

void VideoPlayer::stateChanged(QMovie::MovieState state)
{
   // not used in this example, left here for reference
   switch(state) {
      case QMovie::NotRunning:
         break;

      case QMovie::Paused:        
         break;

      case QMovie::Running:

         break;
   }
}

void VideoPlayer::frameChanged(int frame)
{
   if (! presentImage(m_movie.currentImage())) {
      m_movie.stop();
      ksMsg("Unable to display image.");
   }
}

bool VideoPlayer::presentImage(const QImage &image)
{
   QVideoFrame frame(image);

   if (! frame.isValid()) {
      return false;
   }

   QVideoSurfaceFormat currentFormat = m_surface->surfaceFormat();

   if (frame.pixelFormat() != currentFormat.pixelFormat()
         || frame.size() != currentFormat.frameSize()) {

      QVideoSurfaceFormat format(frame.size(), frame.pixelFormat());

      if (! m_surface->start(format)) {
         return false;
      }
   }

   if (! m_surface->present(frame)) {
      m_surface->stop();
      return false;

   } else {
      return true;

   }
}

void VideoPlayer::actionClose() {
   this->parentWidget()->close();
}
