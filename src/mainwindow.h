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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ui_mainwindow.h>

#include <QMainWindow>

class MainWindow : public QMainWindow
{
   CS_OBJECT(MainWindow)

   public:
      explicit MainWindow();
      ~MainWindow();
      void addMdiChild(QWidget *);

   private:
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
      CS_SLOT_1(Private, void actionCamera())
      CS_SLOT_2(actionCamera)

      CS_SLOT_1(Private, void actionMusicPlayer())
      CS_SLOT_2(actionMusicPlayer)

      CS_SLOT_1(Private, void actionVideoWidget())
      CS_SLOT_2(actionVideoWidget)

      CS_SLOT_1(Private, void actionHTML_Viewer())
      CS_SLOT_2(actionHTML_Viewer)

      CS_SLOT_1(Private, void actionWebBrowser())
      CS_SLOT_2(actionWebBrowser)

      //
      CS_SLOT_1(Private, void actionChat())
      CS_SLOT_2(actionChat)

      CS_SLOT_1(Private, void actionSsl())
      CS_SLOT_2(actionChat)

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

      Ui::MainWindow *m_ui;
      void changeEvent(QEvent *event);
};

#endif
