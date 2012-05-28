/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include "util.h"
#include "web_browser.h"

#include <QtGui>
#include <QtWebKit>

WebBrowser::WebBrowser(Mdi *parent)
   : QMainWindow()
{
   m_parent   = parent;
   m_progress = 0;

   QNetworkProxyFactory::setUseSystemConfiguration(true);

   m_view = new QWebView(this);

   QUrl url = QUrl("http://www.google.com");
   m_view->load(url);

   //
   m_urlEdit = new QLineEdit(this);
   m_urlEdit->setSizePolicy(QSizePolicy::Expanding, m_urlEdit->sizePolicy().verticalPolicy());

   QFont font = m_urlEdit->font();
   font.setPointSize(font.pointSize()+2);
   m_urlEdit->setFont(font);

   //
   QToolBar *toolBar = addToolBar(tr("Navigation"));
   toolBar->addAction(m_view->pageAction(QWebPage::Back));
   toolBar->addAction(m_view->pageAction(QWebPage::Forward));
   toolBar->addAction(m_view->pageAction(QWebPage::Reload));
   toolBar->addAction(m_view->pageAction(QWebPage::Stop));
   toolBar->addWidget(m_urlEdit);

   //
   QMenu *viewMenu = menuBar()->addMenu(tr("&File"));
   QAction* fileaction_1 = new QAction("Page Source", this);
   connect(fileaction_1, SIGNAL(triggered()), SLOT(getSource()));
   viewMenu->addAction(fileaction_1);

   QAction* fileaction_2 = new QAction("Exit Browser", this);
   connect(fileaction_2, SIGNAL(triggered()), SLOT(actionClose()));
   viewMenu->addAction(fileaction_2);

   //
   QMenu *toolsMenu = menuBar()->addMenu(tr("&Bookmarks"));
   toolsMenu->addAction(tr("Astronomy Picture"),      this, SLOT(goNasa()));
   toolsMenu->addAction(tr("Cooking for Engineers"),  this, SLOT(goFood()));
   toolsMenu->addAction(tr("CopperSpice"),            this, SLOT(goCS()));
   toolsMenu->addAction(tr("Google"),                 this, SLOT(goGoogle()));
   toolsMenu->addAction(tr("Huffington Post"),        this, SLOT(goHuffPo()));
   toolsMenu->addAction(tr("Slashdot"),               this, SLOT(goSlash()));
   toolsMenu->addAction(tr("Wikipedia"),              this, SLOT(goWiki()));

   // signals
   connect(m_urlEdit, SIGNAL(returnPressed()),           SLOT(changeLocation()));
   connect(m_view,    SIGNAL(loadProgress(int)),         SLOT(setProgress(int)));
   connect(m_view,    SIGNAL(loadFinished(bool)),        SLOT(setLocation()));
   connect(m_view,    SIGNAL(titleChanged(QString)),     SLOT(setTitle()));

  // connect(m_view->page(),  SIGNAL(linkHovered(const QString &, const QString &, const QString &)),
  //                                SLOT(actionLinkHovered(const QString &, const QString &, const QString &)) );

   setCentralWidget(m_view);
   setUnifiedTitleAndToolBarOnMac(true);
}

void WebBrowser::changeLocation()
{
   QString urlString = m_urlEdit->text();

   QUrl url = QUrl(urlString);

   // test for scheme
   QString temp = url.scheme();
   if ( temp.isEmpty() ) {
      urlString = "http://" + urlString;

      // regenerate
      url = QUrl(urlString);
   }

   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::setLocation()
{
   m_urlEdit->setText(m_view->url().toString());
}

void WebBrowser::setProgress(int p)
{
   m_progress = p;
   setTitle();
}

void WebBrowser::setTitle()
{
   if (m_progress <= 0 || m_progress >= 100) {
      setWindowTitle(m_view->title());
   } else {
      setWindowTitle(QString("%1 (%2%)").arg(m_view->title()).arg(m_progress));
   }
}

void WebBrowser::actionLinkHovered(const QString & link, const QString & title, const QString & textContent)
{

   bgMsg("A");

   bgMsg(link);

   bgMsg("B");


}

void WebBrowser::getSource()
{
   QNetworkAccessManager* accessManager = m_view->page()->networkAccessManager();
   QNetworkRequest request(m_view->url());
   QNetworkReply* reply = accessManager->get(request);
   connect(reply, SIGNAL(finished()), this, SLOT(displaySource()));
}

void WebBrowser::displaySource()
{
   QNetworkReply* reply = qobject_cast<QNetworkReply*>(const_cast<QObject*>(sender()));

   QMainWindow *temp = new QMainWindow();
   temp->setWindowTitle("Page Source");

   QTextEdit* textEdit  = new QTextEdit(temp);
   textEdit->setAttribute(Qt::WA_DeleteOnClose);
   textEdit->setPlainText(reply->readAll());
   textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

   temp->setCentralWidget(textEdit);
   m_parent->addMdiChild(temp);

   //
   reply->deleteLater();
}

void WebBrowser::goNasa()
{
   QUrl url = QUrl("http://apod.nasa.gov");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goCS()
{
   QUrl url = QUrl("http://192.168.10.39/copperspice/");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goFood()
{
   QUrl url = QUrl("http://www.cookingforengineers.com");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goGoogle()
{
   QUrl url = QUrl("http://www.google.com");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goHuffPo()
{
   QUrl url = QUrl("http://www.huffingtonpost.com");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goSlash()
{
   QUrl url = QUrl("http://www.slashdot.org");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goWiki()
{
   QUrl url = QUrl("http://en.wikipedia.org");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::actionClose() {
   this->parentWidget()->close();
}






