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

#ifndef MDI_H
#define MDI_H

#include "ui_mdi.h"

#include <QtGui/QMainWindow>

class Mdi : public QMainWindow
{
   Q_OBJECT

   public:
      explicit Mdi();
      ~Mdi();
      void addMdiChild(QWidget *);     

   private:
      Ui::Mdi *ui;
      void changeEvent(QEvent *event);

   private slots:
      void on_actionClose_Window_triggered();
      void on_actionCloseAll_Windows_triggered();
      void on_actionExit_Program_triggered();

      void on_actionColorPicker_triggered();
      void on_actionFonts_triggered();
      void on_actionDraw_triggered();
      void on_actionInternational_triggered();        
      void on_actionSystemTray_triggered();
      void on_actionSvgView_triggered();

      void on_actionStandardDialog_triggered();
      void on_actionStandardPath_triggered();
      void on_actionStyleSheetDialog_triggered();          
      void on_actionScript_triggered();
      void on_actionXml_triggered();

      void on_actionMusicPlayer_triggered();
      void on_actionVideoWidget_triggered();
      void on_actionHTML_Viewer_triggered();
      void on_actionWebBrowser_triggered();

      void on_actionTableView_triggered();
      void on_actionTreeView_triggered();
      void on_actionListView_triggered();
      void on_actionTableWidget_View_triggered();

      void on_actionCalendar_triggered();
      void on_actionLineEdit_triggered();      
      void on_actionSliders_triggered();
      void on_actionTabs_triggered();

      void on_actionAbout_CopperSpice_triggered();
      void on_actionAbout_triggered();     
};

#endif
