/**********************************************************************
*
* Copyright (c) 2012 Barbara Geller
* Copyright (c) 2011 Nokia Corporation and/or its subsidiary(-ies).
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
#include "aboutcs.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>

AboutCS::AboutCS()
   : QWidget()
{
   setWindowTitle("About CopperSpice");

   QPushButton *homePB  = new QPushButton;
   homePB->setText("Home");

   QPushButton *closePB = new QPushButton;
   closePB->setText("Close");

   //
   m_viewer = new QWebView;

   QString url = "http://www.copperspice.com/kitchensink.html";
   m_viewer->setUrl(url);

   //
   QHBoxLayout *buttonLayout = new QHBoxLayout;
   buttonLayout->addStretch();
   buttonLayout->addWidget(homePB);
   buttonLayout->addSpacing(10);
   buttonLayout->addWidget(closePB);
   buttonLayout->addStretch();

   QVBoxLayout *mainLayout = new QVBoxLayout;
   mainLayout->addWidget(m_viewer);
   mainLayout->addSpacing(10);
   mainLayout->addLayout(buttonLayout);
   setLayout(mainLayout);

   mainLayout->setContentsMargins(0, 0, 0, 15);

   QSize size = QSize(1100, 700);
   resize(size);

   // signals
   connect(homePB,   SIGNAL(clicked()), this, SLOT(actionHome()) );
   connect(closePB,  SIGNAL(clicked()), this, SLOT(actionClose()) );  
}

void AboutCS::actionHome() {
   QString url = "http://www.copperspice.com/kitchensink.html";
   m_viewer->setUrl(url);
}

void AboutCS::actionClose() {
   this->parentWidget()->close();
}
