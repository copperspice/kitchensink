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

#if ! defined(QT_NO_WEBKIT)

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
      url = QUrl("https://www.copperspice.com");
      setWindowTitle("About CopperSpice");

   } else   {
      url = QUrl("https://www.copperspice.com/documentation-kitchensink.html");
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
   connect(homePB,  &QPushButton::clicked, this, &AboutCS::actionHome );
   connect(closePB, &QPushButton::clicked, this, &AboutCS::actionClose);
}

void AboutCS::actionHome() {
   QUrl url("https://www.copperspice.com/documentation-kitchensink.html");
   m_viewer->setUrl(url);
}

void AboutCS::actionClose() {
   this->parentWidget()->close();
}

QSize AboutCS::sizeHint() const
{
   return QSize(800, 600);
}

#endif