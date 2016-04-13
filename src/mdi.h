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

#ifndef MDI_H
#define MDI_H

#include "ui_mdi.h"

#include <QtGui/QMainWindow>

class Mdi : public QMainWindow
{
   CS_OBJECT(Mdi)

   public:
      explicit Mdi();
      ~Mdi();
      void addMdiChild(QWidget *);     

   private:
      Ui::Mdi *ui;
      void changeEvent(QEvent *event);

      CS_SLOT_1(Private, void on_actionClose_Window_triggered())
      CS_SLOT_2(on_actionClose_Window_triggered) 

      CS_SLOT_1(Private, void on_actionCloseAll_Windows_triggered())
      CS_SLOT_2(on_actionCloseAll_Windows_triggered) 

      CS_SLOT_1(Private, void on_actionExit_Program_triggered())
      CS_SLOT_2(on_actionExit_Program_triggered) 

      CS_SLOT_1(Private, void on_actionColorPicker_triggered())
      CS_SLOT_2(on_actionColorPicker_triggered) 

      CS_SLOT_1(Private, void on_actionFonts_triggered())
      CS_SLOT_2(on_actionFonts_triggered) 

      CS_SLOT_1(Private, void on_actionDraw_triggered())
      CS_SLOT_2(on_actionDraw_triggered) 

      CS_SLOT_1(Private, void on_actionInternational_triggered())
      CS_SLOT_2(on_actionInternational_triggered)         

      CS_SLOT_1(Private, void on_actionSystemTray_triggered())
      CS_SLOT_2(on_actionSystemTray_triggered) 

      CS_SLOT_1(Private, void on_actionSvgView_triggered())
      CS_SLOT_2(on_actionSvgView_triggered) 

      //
      CS_SLOT_1(Private, void on_actionStandardDialog_triggered())
      CS_SLOT_2(on_actionStandardDialog_triggered) 

      CS_SLOT_1(Private, void on_actionStandardPath_triggered())
      CS_SLOT_2(on_actionStandardPath_triggered) 

      CS_SLOT_1(Private, void on_actionStyleSheetDialog_triggered())
      CS_SLOT_2(on_actionStyleSheetDialog_triggered)           

      CS_SLOT_1(Private, void on_actionScript_triggered())
      CS_SLOT_2(on_actionScript_triggered) 

      CS_SLOT_1(Private, void on_actionXml_triggered())
      CS_SLOT_2(on_actionXml_triggered) 

      CS_SLOT_1(Private, void on_actionXmlPatterns_triggered())
      CS_SLOT_2(on_actionXmlPatterns_triggered)

      //
      CS_SLOT_1(Private, void on_actionMusicPlayer_triggered())
      CS_SLOT_2(on_actionMusicPlayer_triggered) 

      CS_SLOT_1(Private, void on_actionVideoWidget_triggered())
      CS_SLOT_2(on_actionVideoWidget_triggered) 

      CS_SLOT_1(Private, void on_actionHTML_Viewer_triggered())
      CS_SLOT_2(on_actionHTML_Viewer_triggered) 

      CS_SLOT_1(Private, void on_actionWebBrowser_triggered())
      CS_SLOT_2(on_actionWebBrowser_triggered) 

      //
      CS_SLOT_1(Private, void on_actionTableView_triggered())
      CS_SLOT_2(on_actionTableView_triggered) 

      CS_SLOT_1(Private, void on_actionTreeView_triggered())
      CS_SLOT_2(on_actionTreeView_triggered) 

      CS_SLOT_1(Private, void on_actionListView_triggered())
      CS_SLOT_2(on_actionListView_triggered) 

      CS_SLOT_1(Private, void on_actionTableWidget_View_triggered())
      CS_SLOT_2(on_actionTableWidget_View_triggered) 

      //
      CS_SLOT_1(Private, void on_actionCalendar_triggered())
      CS_SLOT_2(on_actionCalendar_triggered) 

      CS_SLOT_1(Private, void on_actionLineEdit_triggered())
      CS_SLOT_2(on_actionLineEdit_triggered)       

      CS_SLOT_1(Private, void on_actionSliders_triggered())
      CS_SLOT_2(on_actionSliders_triggered) 

      CS_SLOT_1(Private, void on_actionTabs_triggered())
      CS_SLOT_2(on_actionTabs_triggered) 

      //
      CS_SLOT_1(Private, void on_actionAnalog_Clock_triggered())
      CS_SLOT_2(on_actionAnalog_Clock_triggered) 

      CS_SLOT_1(Private, void on_actionAnimated_Tiles_triggered())
      CS_SLOT_2(on_actionAnimated_Tiles_triggered) 

      CS_SLOT_1(Private, void on_actionFridge_Magnets_triggered())
      CS_SLOT_2(on_actionFridge_Magnets_triggered) 

      CS_SLOT_1(Private, void on_actionGrabber_triggered())
      CS_SLOT_2(on_actionGrabber_triggered) 

      CS_SLOT_1(Private, void on_actionLighting_triggered())
      CS_SLOT_2(on_actionLighting_triggered) 

      CS_SLOT_1(Private, void on_actionMandelbrot_triggered())      
      CS_SLOT_2(on_actionMandelbrot_triggered)

      CS_SLOT_1(Private, void on_actionScreen_Shot_triggered())
      CS_SLOT_2(on_actionScreen_Shot_triggered) 

      CS_SLOT_1(Private, void on_actionWiggle_Boxes_triggered())
      CS_SLOT_2(on_actionWiggle_Boxes_triggered) 

      CS_SLOT_1(Private, void on_actionWorld_Clock_triggered())
      CS_SLOT_2(on_actionWorld_Clock_triggered) 

      //
      CS_SLOT_1(Private, void on_actionAbout_CopperSpice_triggered())
      CS_SLOT_2(on_actionAbout_CopperSpice_triggered) 

      CS_SLOT_1(Private, void on_actionAbout_KitchenSink_triggered())
      CS_SLOT_2(on_actionAbout_KitchenSink_triggered)

      CS_SLOT_1(Private, void on_actionAbout_triggered())
      CS_SLOT_2(on_actionAbout_triggered)      
};

#endif
