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
      Ui::Mdi *m_ui;
      void changeEvent(QEvent *event);

      CS_SLOT_1(Private, void actionClose_Window())
      CS_SLOT_2(actionClose_Window)

      CS_SLOT_1(Private, void actionCloseAll_Windows())
      CS_SLOT_2(actionCloseAll_Windows)

      CS_SLOT_1(Private, void actionExit_Program())
      CS_SLOT_2(actionExit_Program)

      CS_SLOT_1(Private, void actionColorPicker())
      CS_SLOT_2(actionColorPicker)

      CS_SLOT_1(Private, void actionFonts())
      CS_SLOT_2(actionFonts)

      CS_SLOT_1(Private, void actionDraw())
      CS_SLOT_2(actionDraw)

      CS_SLOT_1(Private, void actionInternational())
      CS_SLOT_2(actionInternational)

      CS_SLOT_1(Private, void actionSystemTray())
      CS_SLOT_2(actionSystemTray)

      CS_SLOT_1(Private, void actionSvgView())
      CS_SLOT_2(actionSvgView)

      //
      CS_SLOT_1(Private, void actionStandardDialog())
      CS_SLOT_2(actionStandardDialog)

      CS_SLOT_1(Private, void actionStandardPath())
      CS_SLOT_2(actionStandardPath)

      CS_SLOT_1(Private, void actionStyleSheetDialog())
      CS_SLOT_2(actionStyleSheetDialog)

      CS_SLOT_1(Private, void actionScript())
      CS_SLOT_2(actionScript)

      CS_SLOT_1(Private, void actionXml())
      CS_SLOT_2(actionXml)

      CS_SLOT_1(Private, void actionXmlPatterns())
      CS_SLOT_2(actionXmlPatterns)

      //
      CS_SLOT_1(Private, void actionMusicPlayer())
      CS_SLOT_2(actionMusicPlayer)

      CS_SLOT_1(Private, void actionVideoWidget())
      CS_SLOT_2(actionVideoWidget)

      CS_SLOT_1(Private, void actionHTML_Viewer())
      CS_SLOT_2(actionHTML_Viewer)

      CS_SLOT_1(Private, void actionWebBrowser())
      CS_SLOT_2(actionWebBrowser)

      //
      CS_SLOT_1(Private, void actionTableView())
      CS_SLOT_2(actionTableView)

      CS_SLOT_1(Private, void actionTreeView())
      CS_SLOT_2(actionTreeView)

      CS_SLOT_1(Private, void actionListView())
      CS_SLOT_2(actionListView)

      CS_SLOT_1(Private, void actionTableWidget_View())
      CS_SLOT_2(actionTableWidget_View)

      //
      CS_SLOT_1(Private, void actionCalendar())
      CS_SLOT_2(actionCalendar)

      CS_SLOT_1(Private, void actionLineEdit())
      CS_SLOT_2(actionLineEdit)

      CS_SLOT_1(Private, void actionSliders())
      CS_SLOT_2(actionSliders)

      CS_SLOT_1(Private, void actionTabs())
      CS_SLOT_2(actionTabs)

      //
      CS_SLOT_1(Private, void actionAnalog_Clock())
      CS_SLOT_2(actionAnalog_Clock)

      CS_SLOT_1(Private, void actionAnimated_Tiles())
      CS_SLOT_2(actionAnimated_Tiles)

      CS_SLOT_1(Private, void actionFridge_Magnets())
      CS_SLOT_2(actionFridge_Magnets)

      CS_SLOT_1(Private, void actionGrabber())
      CS_SLOT_2(actionGrabber)

      CS_SLOT_1(Private, void actionLighting())
      CS_SLOT_2(actionLighting)

      CS_SLOT_1(Private, void actionMandelbrot())
      CS_SLOT_2(actionMandelbrot)

      CS_SLOT_1(Private, void actionScreen_Shot())
      CS_SLOT_2(actionScreen_Shot)

      CS_SLOT_1(Private, void actionWiggle_Boxes())
      CS_SLOT_2(actionWiggle_Boxes)

      CS_SLOT_1(Private, void actionWorld_Clock())
      CS_SLOT_2(actionWorld_Clock)

      //
      CS_SLOT_1(Private, void actionAbout_CopperSpice())
      CS_SLOT_2(actionAbout_CopperSpice)

      CS_SLOT_1(Private, void actionAbout_KitchenSink())
      CS_SLOT_2(actionAbout_KitchenSink)

      CS_SLOT_1(Private, void actionAbout())
      CS_SLOT_2(actionAbout)
};

#endif
