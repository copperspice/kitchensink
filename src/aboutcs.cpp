/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#include "aboutcs.h"
#include "util.h"

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSize>
#include <QWebView>

AboutCS::AboutCS(QString route)
   : QWidget()
{
   QUrl url;

   if (route == "cs")  {
      url = QUrl("http://www.copperspice.com");
      setWindowTitle("About CopperSpice");

   } else   {
      url = QUrl("http://www.copperspice.com/documentation-kitchensink.html");
      setWindowTitle("About KitchenSink");

   }

   QPushButton *homePB  = new QPushButton;
   homePB->setText("Home");

   QPushButton *closePB = new QPushButton;
   closePB->setText("Close");

   //
   m_viewer = new QWebView;
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

   // signals
   connect(homePB,  SIGNAL(clicked()), this, SLOT(actionHome()) );
   connect(closePB, SIGNAL(clicked()), this, SLOT(actionClose()) );
}

void AboutCS::actionHome() {
   QUrl url("http://www.copperspice.com/kitchensink.html");
   m_viewer->setUrl(url);
}

void AboutCS::actionClose() {
   this->parentWidget()->close();
}

QSize AboutCS::sizeHint() const
{
   return QSize(800, 600);
}
