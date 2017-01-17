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

#ifndef WEB_BROWSER_H
#define WEB_BROWSER_H

#include "mdi.h"

#include <QtGui>
#include <QLineEdit>
#include <QWebView>

class WebBrowser : public QMainWindow
{
   CS_OBJECT(WebBrowser)

   public:
      WebBrowser(Mdi *parent, QUrl url = QUrl() );

   protected :
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
      QWebView  *m_view;
      QLineEdit *m_urlEdit;

      Mdi *m_parent;
      int  m_progress;      
};

#endif
