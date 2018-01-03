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

#ifndef WEB_BROWSER_H
#define WEB_BROWSER_H

#include "mainwindow.h"

#include <QMainWindow>
#include <QWebView>

class QLineEdit;

class WebBrowser : public QMainWindow
{
   CS_OBJECT(WebBrowser)

   public:
      WebBrowser(MainWindow *parent, QUrl url = QUrl() );

   protected:
      CS_SLOT_1(Protected, void changeLocation())
      CS_SLOT_2(changeLocation)

      CS_SLOT_1(Protected, void setTitle())
      CS_SLOT_2(setTitle)

      CS_SLOT_1(Protected, void setLocation())
      CS_SLOT_2(setLocation)

      CS_SLOT_1(Protected, void setProgress(int p))
      CS_SLOT_2(setProgress)

      CS_SLOT_1(Protected, void actionLinkHovered(const QString &link,const QString &title,const QString &textContent))
      CS_SLOT_2(actionLinkHovered)

      CS_SLOT_1(Protected, void actionDevTool(bool checked))
      CS_SLOT_2(actionDevTool)

      CS_SLOT_1(Protected, void actionJavaScript(bool checked))
      CS_SLOT_2(actionJavaScript)

      CS_SLOT_1(Protected, void actionPlugins(bool checked))
      CS_SLOT_2(actionPlugins)

      CS_SLOT_1(Protected, void setCustomContextMenu(const QPoint &pos))
      CS_SLOT_2(setCustomContextMenu)

      CS_SLOT_1(Protected, void actionOpenNewWindow())
      CS_SLOT_2(actionOpenNewWindow)

      CS_SLOT_1(Protected, void actionOpenInNewTab())
      CS_SLOT_2(actionOpenInNewTab)

      CS_SLOT_1(Protected, void actionDownloadLinkToDisk())
      CS_SLOT_2(actionDownloadLinkToDisk)

      CS_SLOT_1(Protected, void downloadFinished())
      CS_SLOT_2(downloadFinished)

      CS_SLOT_1(Protected, void goNasa())
      CS_SLOT_2(goNasa)

      CS_SLOT_1(Protected, void goCS())
      CS_SLOT_2(goCS)

      CS_SLOT_1(Protected, void goFood())
      CS_SLOT_2(goFood)

      CS_SLOT_1(Protected, void goGoogle())
      CS_SLOT_2(goGoogle)

      CS_SLOT_1(Protected, void goHuffPo())
      CS_SLOT_2(goHuffPo)

      CS_SLOT_1(Protected, void goSlash())
      CS_SLOT_2(goSlash)

      CS_SLOT_1(Protected, void goWiki())
      CS_SLOT_2(goWiki)

      CS_SLOT_1(Protected, void goYouTube())
      CS_SLOT_2(goYouTube)

      CS_SLOT_1(Protected, void getSource())
      CS_SLOT_2(getSource)

      CS_SLOT_1(Protected, void displaySource())
      CS_SLOT_2(displaySource)

      CS_SLOT_1(Protected, void actionClose())
      CS_SLOT_2(actionClose)

   private:
      MainWindow *m_parent;
      QWebView   *m_view;
      QLineEdit  *m_urlEdit;
      int  m_progress;
};

#endif
