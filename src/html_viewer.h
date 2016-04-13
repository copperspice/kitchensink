/**********************************************************************
*
* Copyright (c) 2012-2016 Barbara Geller
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

#ifndef HTML_VIEWER_H
#define HTML_VIEWER_H

#include "ui_html_viewer.h"

#include <QMainWindow>
#include <QMenu>

class Html_Viewer : public QMainWindow
{
   CS_OBJECT(Html_Viewer)

   public:
      Html_Viewer();
      ~Html_Viewer();

   private:
      Ui::Html_Form *ui;
      QUrl m_baseUrl;

      void createActions();     
      void setStartupText();
   
      CS_SLOT_1(Private, void about())
      CS_SLOT_2(about) 

      CS_SLOT_1(Private, void open())
      CS_SLOT_2(open) 

      CS_SLOT_1(Private, void openUrl())
      CS_SLOT_2(openUrl) 

      CS_SLOT_1(Private, void save())
      CS_SLOT_2(save) 

      CS_SLOT_1(Private, void updateTextEdit())
      CS_SLOT_2(updateTextEdit) 

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose) 

      CS_SLOT_1(Private, void actionPreview())
      CS_SLOT_2(actionPreview) 
};


#endif
