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

#include <ks_build_info.h>
#include <mainwindow.h>
#include <util.h>

#include <colorpicker.h>
#include <dialogs.h>
#include <draw.h>
#include <fontpicker.h>
#include <international.h>
#include <stdpath.h>
#include <style_dw.h>
#include <systray.h>
#include <svg_view.h>
#include <videoplayer.h>
#include <xml.h>
#include <xmlpatterns.h>

#if ! defined(QT_NO_MULTIMEDIA)
#include <camera.h>
#include <musicplayer.h>
#endif

#if ! defined(QT_NO_WEBKIT)
#include <aboutcs.h>
#include <html_viewer.h>
#include <web_browser.h>
#endif

#include <analogclock.h>
#include <animated_tiles.h>
#include <fridgemag.h>
#include <grabber.h>
#include <lighting.h>
#include <mandelbrot_widget.h>
#include <screenshot.h>

#include <chat_dialog.h>
#include <ssl_client.h>

#include <listview.h>
#include <tableview.h>
#include <tablewidget_view.h>
#include <treeview.h>

#include <calendar.h>
#include <line_edit.h>
#include <sliders.h>
#include <tabdialog.h>

// #include "script.h"       (QScript)
// #include "wiggle_boxes.h" (Qml)
// #include "world_clock.h"  (Qml)

#include <QMdiSubWindow>

MainWindow::MainWindow()
   : QMainWindow(), m_ui(new Ui::MainWindow)
{
   m_ui->setupUi(this);

   setWindowTitle(tr("KitchenSink"));
   setWindowIcon(QIcon("://resources/ks.ico"));

/*
   // future usage

   m_ui->menuWidgets->setToolTipsVisible(true);
   // m_ui->menuWidgets->setToolTipDuration(60000);  // 60 secs
   m_ui->actionTabs->setToolTip("Source File: widgets/tabdialog.cpp");
*/

#if defined(QT_NO_WEBKIT)
   // webkit temporarily removed, pending overflow issue resolution in CsWebKit
   m_ui->actionAbout_CopperSpice->setVisible(false);
   m_ui->actionAbout_KitchenSink->setVisible(false);
#endif

   connect(m_ui->actionClose_Window,      &QAction::triggered, this,  &MainWindow::actionClose_Window);
   connect(m_ui->actionCloseAll_Windows,  &QAction::triggered, this,  &MainWindow::actionCloseAll_Windows);
   connect(m_ui->actionExit_Program,      &QAction::triggered, this,  &MainWindow::actionExit_Program);

   connect(m_ui->actionColorPicker,       &QAction::triggered, this,  &MainWindow::actionColorPicker);
   connect(m_ui->actionFonts,             &QAction::triggered, this,  &MainWindow::actionFonts);
   connect(m_ui->actionDraw,              &QAction::triggered, this,  &MainWindow::actionDraw);
   connect(m_ui->actionInternational,     &QAction::triggered, this,  &MainWindow::actionInternational);
   connect(m_ui->actionSystemTray,        &QAction::triggered, this,  &MainWindow::actionSystemTray);
   connect(m_ui->actionSvgView,           &QAction::triggered, this,  &MainWindow::actionSvgView);
   connect(m_ui->actionStandardDialog,    &QAction::triggered, this,  &MainWindow::actionStandardDialog);
   connect(m_ui->actionStandardPath,      &QAction::triggered, this,  &MainWindow::actionStandardPath);
   connect(m_ui->actionStyleSheetDialog,  &QAction::triggered, this,  &MainWindow::actionStyleSheetDialog);
   connect(m_ui->actionScript,            &QAction::triggered, this,  &MainWindow::actionScript);
   connect(m_ui->actionXml,               &QAction::triggered, this,  &MainWindow::actionXml);
   connect(m_ui->actionXmlPatterns,       &QAction::triggered, this,  &MainWindow::actionXmlPatterns);

   connect(m_ui->actionCamera,            &QAction::triggered, this,  &MainWindow::actionCamera);
   connect(m_ui->actionMusicPlayer,       &QAction::triggered, this,  &MainWindow::actionMusicPlayer);
   connect(m_ui->actionVideoWidget,       &QAction::triggered, this,  &MainWindow::actionVideoWidget);
   connect(m_ui->actionHTML_Viewer,       &QAction::triggered, this,  &MainWindow::actionHTML_Viewer);
   connect(m_ui->actionWebBrowser,        &QAction::triggered, this,  &MainWindow::actionWebBrowser);

   connect(m_ui->actionChat,              &QAction::triggered, this,  &MainWindow::actionChat);
   connect(m_ui->actionSsl,               &QAction::triggered, this,  &MainWindow::actionSsl);

   connect(m_ui->actionTableView,         &QAction::triggered, this,  &MainWindow::actionTableView);
   connect(m_ui->actionTreeView,          &QAction::triggered, this,  &MainWindow::actionTreeView);
   connect(m_ui->actionListView,          &QAction::triggered, this,  &MainWindow::actionListView);
   connect(m_ui->actionTableWidget_View,  &QAction::triggered, this,  &MainWindow::actionTableWidget_View);

   connect(m_ui->actionCalendar,          &QAction::triggered, this,  &MainWindow::actionCalendar);
   connect(m_ui->actionLineEdit,          &QAction::triggered, this,  &MainWindow::actionLineEdit);
   connect(m_ui->actionSliders,           &QAction::triggered, this,  &MainWindow::actionSliders);
   connect(m_ui->actionTabs,              &QAction::triggered, this,  &MainWindow::actionTabs);

   connect(m_ui->actionAnalog_Clock,      &QAction::triggered, this,  &MainWindow::actionAnalog_Clock);
   connect(m_ui->actionAnimated_Tiles,    &QAction::triggered, this,  &MainWindow::actionAnimated_Tiles);
   connect(m_ui->actionFridge_Magnets,    &QAction::triggered, this,  &MainWindow::actionFridge_Magnets);
   connect(m_ui->actionGrabber,           &QAction::triggered, this,  &MainWindow::actionGrabber);
   connect(m_ui->actionLighting,          &QAction::triggered, this,  &MainWindow::actionLighting);
   connect(m_ui->actionMandelbrot,        &QAction::triggered, this,  &MainWindow::actionMandelbrot);
   connect(m_ui->actionScreen_Shot,       &QAction::triggered, this,  &MainWindow::actionScreen_Shot);
   connect(m_ui->actionWiggle_Boxes,      &QAction::triggered, this,  &MainWindow::actionWiggle_Boxes);
   connect(m_ui->actionWorld_Clock,       &QAction::triggered, this,  &MainWindow::actionWorld_Clock);

   connect(m_ui->actionAbout_CopperSpice, &QAction::triggered, this,  &MainWindow::actionAbout_CopperSpice);
   connect(m_ui->actionAbout_KitchenSink, &QAction::triggered, this,  &MainWindow::actionAbout_KitchenSink);
   connect(m_ui->actionAbout,             &QAction::triggered, this,  &MainWindow::actionAbout);

#ifdef Q_OS_MAC
   setUnifiedTitleAndToolBarOnMac(true);
#endif

}

MainWindow::~MainWindow()
{
   delete m_ui;
}

void MainWindow::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      m_ui->retranslateUi(this);
   }

   // calls parent, will change the title bar
   QMainWindow::changeEvent(event);
}

void MainWindow::addMdiChild(QWidget *oDw)
{
   QMdiSubWindow *subWindow = m_ui->mdiArea->addSubWindow(oDw);
   subWindow->show();
}

// file
void MainWindow::actionClose_Window()
{
   QMdiSubWindow *temp = m_ui->mdiArea->currentSubWindow();

   if (temp) {
      temp->close();
   }
}

void MainWindow::actionCloseAll_Windows()
{
   m_ui->mdiArea->closeAllSubWindows();
}

void MainWindow::actionExit_Program()
{
   close();
}


// samples
void MainWindow::actionColorPicker()
{
   ColorPicker *oDw = new ColorPicker();
   addMdiChild(oDw);
}

void MainWindow::actionFonts()
{
   FontPicker *oDw = new FontPicker();
   addMdiChild(oDw);
}

void MainWindow::actionDraw()
{
   Draw *oDw = new Draw();
   addMdiChild(oDw);
}

void MainWindow::actionInternational()
{
   International *oDw = new International();
   addMdiChild(oDw);
}

void MainWindow::actionSystemTray()
{
   SysTray *oDw = new SysTray();
   addMdiChild(oDw);
}

void MainWindow::actionSvgView()
{
   Svg_View *oDw = new Svg_View();
   addMdiChild(oDw);
}

void MainWindow::actionStandardDialog()
{
   Dialogs *oDw = new Dialogs();
   addMdiChild(oDw);
}

void MainWindow::actionStandardPath()
{
   StdPath *oDw = new StdPath();
   addMdiChild(oDw);
}

void MainWindow::actionStyleSheetDialog()
{
   Style_DW *oDw = new Style_DW(this);
   addMdiChild(oDw);
}

void MainWindow::actionScript()
{
   ksMsg("JS Scripts - CsScript is not available");

/*
   Script *oDw = new Script();
   addMdiChild(oDw);
*/
}

void MainWindow::actionXml()
{
   Xml *oDw = new Xml();
   addMdiChild(oDw);
}

void MainWindow::actionXmlPatterns()
{
   XmlPatterns *oDw = new XmlPatterns();
   addMdiChild(oDw);
}

// audio & visual
void MainWindow::actionCamera()
{

#if ! defined(QT_NO_MULTIMEDIA)
   try {
      Camera *oDw = new Camera();
      addMdiChild(oDw);
   } catch (...) {
      ksMsg(this, "Audio/Video Issue", "No camera or capture device was found.");
   }

 #else
   ksMsg("KS was not built with CsMultimedia library, Camera disabled.");
#endif

}

void MainWindow::actionMusicPlayer()
{

#if ! defined(QT_NO_MULTIMEDIA)
   MusicPlayer *oDw = new MusicPlayer();
   addMdiChild(oDw);
 #else
   ksMsg("KS was not built with CsMultimedia library, MusicPlayer disabled.");
#endif

}

void MainWindow::actionVideoWidget()
{
   VideoPlayer *oDw = new VideoPlayer();
   addMdiChild(oDw);
}

void MainWindow::actionHTML_Viewer()
{
#if ! defined(QT_NO_WEBKIT)
   Html_Viewer *oDw = new Html_Viewer();
   addMdiChild(oDw);
#else
   ksMsg("KS was not built with CsWebkit library, Html Viewer disabled.");
#endif
}

void MainWindow::actionWebBrowser()
{
#if ! defined(QT_NO_WEBKIT)
   WebBrowser *oDw = new WebBrowser(this);
   addMdiChild(oDw);
#else
   ksMsg("KS was not built with CsWebkit library, WebBrowser disabled.");
#endif
}

// network
void MainWindow::actionChat()
{
   Chat_Dialog *oDw = new Chat_Dialog();
   addMdiChild(oDw);
}

void MainWindow::actionSsl()
{

#ifdef QT_SSL
   Ssl_Client *oDw = new Ssl_Client();
   addMdiChild(oDw);

#else
   QMessageBox::information(this, "Secure Socket", "This build of the KitchenSink program does not support SSL.");

#endif

}

// views
void MainWindow::actionTableView()
{
   TableView *oDw = new TableView();
   addMdiChild(oDw);
}

void MainWindow::actionTreeView()
{
   TreeView *oDw = new TreeView();
   addMdiChild(oDw);
}

void MainWindow::actionListView()
{
   ListView *oDw = new ListView();
   addMdiChild(oDw);
}

void MainWindow::actionTableWidget_View()
{
   TableWidget_View *oDw = new TableWidget_View();
   addMdiChild(oDw);
}


// widgets
void MainWindow::actionCalendar()
{
   Calendar *oDw = new Calendar();
   addMdiChild(oDw);
}

void MainWindow::actionLineEdit()
{
   LineEdit *oDw = new LineEdit();
   addMdiChild(oDw);
}

void MainWindow::actionSliders()
{
   Sliders *oDw = new Sliders();
   addMdiChild(oDw);
}

void MainWindow::actionTabs()
{
   TabDialog *oDw = new TabDialog();
   addMdiChild(oDw);
}

// graphics
void MainWindow::actionAnalog_Clock()
{
   AnalogClock *oDw = new AnalogClock();
   addMdiChild(oDw);
}

void MainWindow::actionAnimated_Tiles()
{
   AnimatedTiles *oDw = new AnimatedTiles();
   addMdiChild(oDw);
}

void MainWindow::actionFridge_Magnets()
{
   FridgeMagnet *oDw = new FridgeMagnet();
   addMdiChild(oDw);
}

void MainWindow::actionGrabber()
{
   Grabber *oDw = new Grabber();
   addMdiChild(oDw);
}

void MainWindow::actionLighting()
{
   Lighting *oDw = new Lighting();
   addMdiChild(oDw);
}

void MainWindow::actionMandelbrot()
{
   Mandelbrot_Widget *oDw = new Mandelbrot_Widget();
   addMdiChild(oDw);
}

void MainWindow::actionScreen_Shot()
{
   Screenshot *oDw = new Screenshot();
   addMdiChild(oDw);
}

void MainWindow::actionWiggle_Boxes()
{
   ksMsg("Wiggle Boxes - CsDeclarative is not available");

/*
   Wiggle_Boxes *oDw = new Wiggle_Boxes();
   addMdiChild(oDw);
*/
}

void MainWindow::actionWorld_Clock()
{
   ksMsg("World Clock - CsDeclarative is not available");

/*
   World_Clock *oDw = new World_Clock();
   addMdiChild(oDw);
*/
}

//  help
void MainWindow::actionAbout_CopperSpice()
{
#if ! defined(QT_NO_WEBKIT)
   AboutCS *oDw = new AboutCS("cs");
   addMdiChild(oDw);
#else
   ksMsg("KitchenSink was not built with CsWebKit library, unable to run About CopperSpice.");
#endif
}

void MainWindow::actionAbout_KitchenSink()
{
#if ! defined(QT_NO_WEBKIT)
   AboutCS *oDw = new AboutCS("ks");
   addMdiChild(oDw);
#else
   ksMsg("KitchenSink was not built with CsWebkit library, unable to run About KitchenSink.");
#endif
}

void MainWindow::actionAbout()
{
   QString textBody = "<font color='#000080'><table style=margin-right:25>"
                      "<tr><td><nobr>Developed by Barbara Geller</nobr></td><td>barbara@copperspice.com</td></tr>"
                      "<tr><td style=padding-right:25><nobr>Developed by Ansel Sermersheim</nobr></td><td>ansel@copperspice.com</td></tr>"
                      "</table></font>"
                      "<br>"
                      "<p><small>Copyright 2012-2021 BG Consulting, released under the 2-Clause BSD license<br>"
                      "This program is provided AS IS with no warranty of any kind.<br></small></p>";

   QMessageBox msgB;
   msgB.setIcon(QMessageBox::NoIcon);
   msgB.setWindowIcon(QIcon("://resources/ks.ico"));
   msgB.setMinimumWidth(2000);

   msgB.setWindowTitle(tr("About KitchenSink"));

   msgB.setText(QString("<p style=margin-right:25><center><h5>Version: %1<br>Build # %2</h5></center></p>")
                .formatArgs(QString::fromLatin1(versionString), QString::fromLatin1(buildDate)));

   msgB.setInformativeText(textBody);

   msgB.setStandardButtons(QMessageBox::Ok);
   msgB.setDefaultButton(QMessageBox::Ok);

   msgB.exec();
}
