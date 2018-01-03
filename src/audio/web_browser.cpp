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

#include "util.h"
#include "web_browser.h"

#include <QAction>
#include <QFont>
#include <QFileDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QToolBar>
#include <QtWebKit>

WebBrowser::WebBrowser(MainWindow *parent, QUrl url)
   : QMainWindow(parent)
{
   m_parent   = parent;
   m_progress = 0;

   QNetworkProxyFactory::setUseSystemConfiguration(true);

   m_view = new QWebView(this);

   if (url.isEmpty()) {
      url = QUrl("http://www.copperspice.com");
   }
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

   // 1
   QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

   QAction* temp1 = new QAction(tr("Page Source"), this);
   connect(temp1, SIGNAL(triggered()), this, SLOT(getSource()));
   fileMenu->addAction(temp1);

   QAction* temp2 = new QAction(tr("Close Browser"), this);
   connect(temp2, SIGNAL(triggered()), this, SLOT(actionClose()));
   fileMenu->addAction(temp2);

   // 2
   QMenu *bookMarkMenu = menuBar()->addMenu(tr("&Bookmarks"));

   bookMarkMenu->addAction(tr("Astronomy Picture"),      this, SLOT(goNasa()));
   bookMarkMenu->addAction(tr("Cooking for Engineers"),  this, SLOT(goFood()));
   bookMarkMenu->addAction(tr("CopperSpice"),            this, SLOT(goCS()));
   bookMarkMenu->addAction(tr("Google"),                 this, SLOT(goGoogle()));
   bookMarkMenu->addAction(tr("Huffington Post"),        this, SLOT(goHuffPo()));
   bookMarkMenu->addAction(tr("Slashdot"),               this, SLOT(goSlash()));
   bookMarkMenu->addAction(tr("Wikipedia"),              this, SLOT(goWiki()));
   bookMarkMenu->addAction(tr("You Tube"),               this, SLOT(goYouTube()));

   // 3
   QMenu *toolsMenu = menuBar()->addMenu(tr("&Tools"));

   QAction* temp3 = new QAction(tr("Enable Developer Tools"), this);
   temp3->setCheckable(true);
   temp3->setChecked(false);
   connect(temp3, SIGNAL(triggered(bool)), this, SLOT(actionDevTool( bool)));
   toolsMenu->addAction(temp3);

   QAction* temp4 = new QAction(tr("Enable JavaScript"), this);
   temp4->setCheckable(true);
   temp4->setChecked(true);
   connect(temp4, SIGNAL(triggered(bool)), this, SLOT(actionJavaScript( bool)));
   toolsMenu->addAction(temp4);

   QAction* temp5 = new QAction(tr("Enable Plugins"), this);
   temp5->setCheckable(true);
   temp5->setChecked(true);
   connect(temp5, SIGNAL(triggered(bool)), this, SLOT(actionPlugins( bool)));
   toolsMenu->addAction(temp5);

   // override default of false
   this->actionPlugins(true);

   // set up custom context menu
   m_view->setContextMenuPolicy(Qt::CustomContextMenu);
   connect(m_view,    SIGNAL(customContextMenuRequested(const QPoint &)), this,
           SLOT(setCustomContextMenu(const QPoint &)) );

   // signals
   connect(m_urlEdit, SIGNAL(returnPressed()),     this, SLOT(changeLocation()));
   connect(m_view,    SIGNAL(loadProgress(int)),   this, SLOT(setProgress(int)));
   connect(m_view,    SIGNAL(loadFinished(bool)),  this, SLOT(setLocation()));
   connect(m_view,    SIGNAL(titleChanged(const QString &)), this, SLOT(setTitle()));

   connect(m_view->page(), SIGNAL(linkHovered(const QString &, const QString &, const QString &)), this,
           SLOT(actionLinkHovered(const QString &, const QString &, const QString &)) );

   setCentralWidget(m_view);
}

void WebBrowser::changeLocation()
{
   QString urlString = m_urlEdit->text();
   QUrl url = QUrl(urlString);

   QString temp = url.scheme();
   if ( temp.isEmpty() ) {
      urlString = "http://" + urlString;

      // try again
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

void WebBrowser::actionLinkHovered(const QString & link, const QString & /* title */, const QString & /* textContent */ )
{
   statusBar()->showMessage(link);
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

void WebBrowser::actionDevTool(bool checked)
{
   // disabled by default
   m_view->page()->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, checked);
}

void WebBrowser::actionJavaScript(bool checked)
{
   // enabled by default
   m_view->page()->settings()->setAttribute(QWebSettings::JavascriptEnabled, checked);
}

void WebBrowser::actionPlugins(bool checked)
{
   // enabled by default
   m_view->page()->settings()->setAttribute(QWebSettings::PluginsEnabled, checked);
}


//  context menu
void WebBrowser::setCustomContextMenu(const QPoint &pos)
{
   QWebHitTestResult testHit = m_view->page()->mainFrame()->hitTestContent(pos);

   QUrl url = testHit.linkUrl();

   if ( ! url.isEmpty()) {

      // retrieves the default menu, can add additional actions
      // QMenu *menu = m_view->page()->createStandardContextMenu();

      //
      QMenu *menu = new QMenu(this);

      menu->addAction(m_view->pageAction(QWebPage::OpenLink));

      QAction *temp1 = menu->addAction(tr("Open New Window"), this, SLOT(actionOpenNewWindow()));
      temp1->setData(url);

      QAction *temp2 = menu->addAction(tr("Open New Tab"),    this, SLOT(actionOpenInNewTab()));
      temp2->setData(url);

      menu->addSeparator();
      QAction *temp3 = menu->addAction(tr("Save Link"),       this, SLOT(actionDownloadLinkToDisk()));
      temp3->setData(url);

      menu->addAction(m_view->pageAction(QWebPage::CopyLinkToClipboard));

      //
      menu->addSeparator();
      if (m_view->page()->settings()->testAttribute(QWebSettings::DeveloperExtrasEnabled)) {
         menu->addAction(m_view->pageAction(QWebPage::InspectElement));
      }

      menu->exec(mapToGlobal(pos));
   }
}

void WebBrowser::actionOpenNewWindow()
{
   // need url

   // next two lines of code are sadly not good C++ code
   // CopperSpice provides a way to pass a parameter to the Slot

   QObject *p = sender();
   QAction *action = qobject_cast<QAction *>(p);

   if (action)  {
      QUrl url = action->data().toUrl();

      WebBrowser *browser = new WebBrowser(m_parent, url);
      m_parent->addMdiChild(browser);
   }
}

void WebBrowser::actionOpenInNewTab( )
{
   ksMsg(this, "Web Browser", "This feature has not been implemented. The WebBrowser can inherit "
         " from QTabWidget to add this functionality.");
}

void WebBrowser::actionDownloadLinkToDisk()
{
   // retrieve url

   // next two lines of code are sadly not good C++ code
   // CopperSpice provides a way to pass a parameter to the Slot

   QObject *p = sender();
   QAction *action = qobject_cast<QAction *>(p);

   if (action)  {
      QUrl url = action->data().toUrl();

      QFileInfo temp = QFileInfo(url.toString());
      QString defaultFileName = temp.fileName();

      QString fileName = QFileDialog::getSaveFileName(this, tr("Save Link"),defaultFileName, tr("All Files (*.*)")  );

      if (! fileName.isEmpty()) {
         // some of the following code was adapted from http://www.linuxjournal.com

         // create a request and save the file name
         QNetworkRequest *newRequest = new QNetworkRequest(url);
         newRequest->setAttribute(QNetworkRequest::User, fileName);

         // request sent to network manager
         QNetworkAccessManager *networkManager = m_view->page()->networkAccessManager();
         QNetworkReply *reply = networkManager->get(*newRequest);

         connect(reply, SIGNAL(finished()), this, SLOT(downloadFinished()));
      }
   }
}

void WebBrowser::downloadFinished()
{
   QObject *p = sender();
   QNetworkReply *reply = qobject_cast<QNetworkReply *>(p);

   //
   QNetworkRequest request = reply->request();

   QVariant temp = request.attribute(QNetworkRequest::User);
   QString fileName = temp.toString();

   QFile file(fileName);

   if (file.open(QFile::ReadWrite)) {
      file.write(reply->readAll());
   }
}


// bookmarks
void WebBrowser::goNasa()
{
   QUrl url = QUrl("http://apod.nasa.gov");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::goCS()
{
   QUrl url = QUrl("http://www.copperspice.com");
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

void WebBrowser::goYouTube()
{
   QUrl url = QUrl("http://www.youtube.com");
   m_view->load(url);
   m_view->setFocus();
}

void WebBrowser::actionClose() {
   this->parentWidget()->close();
}

