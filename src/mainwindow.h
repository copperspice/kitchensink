/***********************************************************************
*
* Copyright (c) 2012-2026 Barbara Geller
* Copyright (c) 2012-2026 Ansel Sermersheim
*
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software which is released under the BSD 2-Clause license.
* For license details refer to the LICENSE provided with this project.
*
* KitchenSink is distributed in the hope that it will be useful,
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

 protected:
   void changeEvent(QEvent *event) override;

 private:
   // slot methods can be declared as standard methods when using method pointers in connect()

   void actionClose_Window();
   void actionCloseAll_Windows();
   void actionExit_Program();

   void actionColorPicker();
   void actionFonts();
   void actionDraw();
   void actionInternational();
   void actionSystemTray();
   void actionSvgView();
   void actionStandardDialog();
   void actionStandardPath();
   void actionStyleSheetDialog();
   void actionXml();
   void actionXmlPatterns();

   void actionCamera();
   void actionMusicPlayer();
   void actionVideoWidget();
   void actionHTML_Viewer();
   void actionWebBrowser();

   void actionChat();
   void actionSsl();

   void actionTableView();
   void actionTreeView();
   void actionListView();
   void actionTableWidget_View();

   void actionCalendar();
   void actionLineEdit();
   void actionSliders();
   void actionTabs();

   void actionAnalog_Clock();
   void actionAnimated_Tiles();
   void actionFridge_Magnets();
   void actionGrabber();
   void actionLighting();
   void actionMandelbrot();
   void actionScreen_Shot();

   void actionAbout_CopperSpice();
   void actionAbout_KitchenSink();
   void actionAbout();

   Ui::MainWindow *m_ui;
};

#endif
