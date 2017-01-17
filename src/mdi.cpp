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

#include "util.h"
#include "aboutcs.h"
#include "calendar.h"
#include "colorpicker.h"
#include "dialogs.h"
#include "draw.h"
#include "fontpicker.h"
#include "html_viewer.h"
#include "international.h"
#include "musicplayer.h"
#include "line_edit.h"
#include "listview.h"
// #include "script.h" (QScript)
#include "stdpath.h"
#include "sliders.h"
#include "style_dw.h"
#include "systray.h"
#include "svg_view.h"
#include "tabdialog.h"
#include "tableview.h"
#include "tablewidget_view.h"
#include "treeview.h"
#include "videoplayer.h"
#include "web_browser.h"
#include "xml.h"
#include "xmlpatterns.h"

#include "analogclock.h"
#include "animated_tiles.h"
#include "fridgemag.h"
#include "grabber.h"
#include "lighting.h"
#include "mandelbrot_widget.h"
#include "screenshot.h"
// #include "wiggle_boxes.h" (Qml)
// #include "world_clock.h" (Qml)

#include "mdi.h"
#include "ui_mdi.h"

#include <QMdiSubWindow>

Mdi::Mdi()
   : QMainWindow(), m_ui(new Ui::Mdi)
{
   m_ui->setupUi(this);
   setWindowTitle(tr("Kitchen Sink-Cs5"));
   setWindowIcon(QIcon("://resources/ks_cs.ico"));

   connect(m_ui->actionClose_Window,      &QAction::triggered, this,  &Mdi::actionClose_Window);
   connect(m_ui->actionCloseAll_Windows,  &QAction::triggered, this,  &Mdi::actionCloseAll_Windows);
   connect(m_ui->actionExit_Program,      &QAction::triggered, this,  &Mdi::actionExit_Program);

   connect(m_ui->actionColorPicker,       &QAction::triggered, this,  &Mdi::actionColorPicker);
   connect(m_ui->actionFonts,             &QAction::triggered, this,  &Mdi::actionFonts);
   connect(m_ui->actionDraw,              &QAction::triggered, this,  &Mdi::actionDraw);
   connect(m_ui->actionInternational,     &QAction::triggered, this,  &Mdi::actionInternational);
   connect(m_ui->actionSystemTray,        &QAction::triggered, this,  &Mdi::actionSystemTray);
   connect(m_ui->actionSvgView,           &QAction::triggered, this,  &Mdi::actionSvgView);
   connect(m_ui->actionStandardDialog,    &QAction::triggered, this,  &Mdi::actionStandardDialog);
   connect(m_ui->actionStandardPath,      &QAction::triggered, this,  &Mdi::actionStandardPath);
   connect(m_ui->actionStyleSheetDialog,  &QAction::triggered, this,  &Mdi::actionStyleSheetDialog);
   connect(m_ui->actionScript,            &QAction::triggered, this,  &Mdi::actionScript);
   connect(m_ui->actionXml,               &QAction::triggered, this,  &Mdi::actionXml);
   connect(m_ui->actionXmlPatterns,       &QAction::triggered, this,  &Mdi::actionXmlPatterns);

   connect(m_ui->actionMusicPlayer,       &QAction::triggered, this,  &Mdi::actionMusicPlayer);
   connect(m_ui->actionVideoWidget,       &QAction::triggered, this,  &Mdi::actionVideoWidget);
   connect(m_ui->actionHTML_Viewer,       &QAction::triggered, this,  &Mdi::actionHTML_Viewer);
   connect(m_ui->actionWebBrowser,        &QAction::triggered, this,  &Mdi::actionWebBrowser);

   connect(m_ui->actionTableView,         &QAction::triggered, this,  &Mdi::actionTableView);
   connect(m_ui->actionTreeView,          &QAction::triggered, this,  &Mdi::actionTreeView);
   connect(m_ui->actionListView,          &QAction::triggered, this,  &Mdi::actionListView);
   connect(m_ui->actionTableWidget_View,  &QAction::triggered, this,  &Mdi::actionTableWidget_View);

   connect(m_ui->actionCalendar,          &QAction::triggered, this,  &Mdi::actionCalendar);
   connect(m_ui->actionLineEdit,          &QAction::triggered, this,  &Mdi::actionLineEdit);
   connect(m_ui->actionSliders,           &QAction::triggered, this,  &Mdi::actionSliders);
   connect(m_ui->actionTabs,              &QAction::triggered, this,  &Mdi::actionTabs);

   connect(m_ui->actionAnalog_Clock,      &QAction::triggered, this,  &Mdi::actionAnalog_Clock);
   connect(m_ui->actionAnimated_Tiles,    &QAction::triggered, this,  &Mdi::actionAnimated_Tiles);
   connect(m_ui->actionFridge_Magnets,    &QAction::triggered, this,  &Mdi::actionFridge_Magnets);
   connect(m_ui->actionGrabber,           &QAction::triggered, this,  &Mdi::actionGrabber);
   connect(m_ui->actionLighting,          &QAction::triggered, this,  &Mdi::actionLighting);
   connect(m_ui->actionMandelbrot,        &QAction::triggered, this,  &Mdi::actionMandelbrot);
   connect(m_ui->actionScreen_Shot,       &QAction::triggered, this,  &Mdi::actionScreen_Shot);
   connect(m_ui->actionWiggle_Boxes,      &QAction::triggered, this,  &Mdi::actionWiggle_Boxes);
   connect(m_ui->actionWorld_Clock,       &QAction::triggered, this,  &Mdi::actionWorld_Clock);

   connect(m_ui->actionAbout_CopperSpice, &QAction::triggered, this,  &Mdi::actionAbout_CopperSpice);
   connect(m_ui->actionAbout_KitchenSink, &QAction::triggered, this,  &Mdi::actionAbout_KitchenSink);
   connect(m_ui->actionAbout,             &QAction::triggered, this,  &Mdi::actionAbout);

   setUnifiedTitleAndToolBarOnMac(true);
}

Mdi::~Mdi()
{
   delete m_ui;
}

void Mdi::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      m_ui->retranslateUi(this);
   }

   // calls parent, will change the title bar
   QMainWindow::changeEvent(event);
}

void Mdi::addMdiChild(QWidget *oDw)
{
   QMdiSubWindow *subWindow = m_ui->mdiArea->addSubWindow(oDw);
   subWindow->show();
}

// file
void Mdi::actionClose_Window()
{
   QMdiSubWindow *temp = m_ui->mdiArea->currentSubWindow();

   if (temp) {
      temp->close();
   }
}

void Mdi::actionCloseAll_Windows()
{
   m_ui->mdiArea->closeAllSubWindows();
}

void Mdi::actionExit_Program()
{
   close();
}


// samples
void Mdi::actionColorPicker()
{
   ColorPicker *oDw = new ColorPicker();
   addMdiChild(oDw);
}

void Mdi::actionFonts()
{
   FontPicker *oDw = new FontPicker();
   addMdiChild(oDw);
}

void Mdi::actionDraw()
{
   Draw *oDw = new Draw();
   addMdiChild(oDw);
}

void Mdi::actionInternational()
{
   International *oDw = new International();
   addMdiChild(oDw);
}

void Mdi::actionSystemTray()
{
   SysTray *oDw = new SysTray();
   addMdiChild(oDw);
}

void Mdi::actionSvgView()
{
   Svg_View *oDw = new Svg_View();
   addMdiChild(oDw);
}

void Mdi::actionStandardDialog()
{
   Dialogs *oDw = new Dialogs();
   addMdiChild(oDw);
}

void Mdi::actionStandardPath()
{
   StdPath *oDw = new StdPath();
   addMdiChild(oDw);
}

void Mdi::actionStyleSheetDialog()
{
   Style_DW *oDw = new Style_DW(this);
   addMdiChild(oDw);
}

void Mdi::actionScript()
{
   ksMsg("JS Scripts - CsScript is not available");

/*
   Script *oDw = new Script();
   addMdiChild(oDw);
*/
}

void Mdi::actionXml()
{
   Xml *oDw = new Xml();
   addMdiChild(oDw);
}

void Mdi::actionXmlPatterns()
{
    XmlPatterns *oDw = new XmlPatterns();
   addMdiChild(oDw);
}

// audio & visual
void Mdi::actionMusicPlayer()
{ 
   MusicPlayer *oDw = new MusicPlayer();

   if ( oDw->loaded() ) {
      addMdiChild(oDw);
   } else {
      delete oDw;
   }
}

void Mdi::actionVideoWidget()
{
   VideoPlayer *oDw = new VideoPlayer();
   addMdiChild(oDw);
}

void Mdi::actionHTML_Viewer()
{
   Html_Viewer *oDw = new Html_Viewer();
   addMdiChild(oDw);
}

void Mdi::actionWebBrowser()
{   
   WebBrowser *oDw = new WebBrowser(this);
   addMdiChild(oDw);
}


// views
void Mdi::actionTableView()
{
   TableView *oDw = new TableView();
   addMdiChild(oDw);
}

void Mdi::actionTreeView()
{
   TreeView *oDw = new TreeView();
   addMdiChild(oDw);
}

void Mdi::actionListView()
{
   ListView *oDw = new ListView();
   addMdiChild(oDw);
}

void Mdi::actionTableWidget_View()
{
   TableWidget_View *oDw = new TableWidget_View();
   addMdiChild(oDw);
}


// widgets
void Mdi::actionCalendar()
{
   Calendar *oDw = new Calendar();
   addMdiChild(oDw);
}

void Mdi::actionLineEdit()
{
   LineEdit *oDw = new LineEdit();
   addMdiChild(oDw);
}

void Mdi::actionSliders()
{
   Sliders *oDw = new Sliders();
   addMdiChild(oDw);
}

void Mdi::actionTabs()
{
   TabDialog *oDw = new TabDialog();
   addMdiChild(oDw);
}

// graphics
void Mdi::actionAnalog_Clock()
{
   AnalogClock *oDw = new AnalogClock();
   addMdiChild(oDw);
}

void Mdi::actionAnimated_Tiles()
{
   AnimatedTiles *oDw = new AnimatedTiles();
   addMdiChild(oDw);
}

void Mdi::actionFridge_Magnets()
{
   FridgeMagnet *oDw = new FridgeMagnet();
   addMdiChild(oDw);
}

void Mdi::actionGrabber()
{
   Grabber *oDw = new Grabber();
   addMdiChild(oDw);
}

void Mdi::actionLighting()
{
   Lighting *oDw = new Lighting();
   addMdiChild(oDw);
}

void Mdi::actionMandelbrot()
{
   Mandelbrot_Widget *oDw = new Mandelbrot_Widget();
   addMdiChild(oDw);
}

void Mdi::actionScreen_Shot()
{
   Screenshot *oDw = new Screenshot();
   addMdiChild(oDw);
}

void Mdi::actionWiggle_Boxes()
{   
   ksMsg("Wiggle Boxes - CsDeclarative is not available");

/*
   Wiggle_Boxes *oDw = new Wiggle_Boxes();
   addMdiChild(oDw);
*/
}

void Mdi::actionWorld_Clock()
{
   ksMsg("World Clock - CsDeclarative is not available");

/*
   World_Clock *oDw = new World_Clock();
   addMdiChild(oDw);
*/
}

//  help
void Mdi::actionAbout_CopperSpice()
{
   AboutCS *oDw = new AboutCS("cs");
   addMdiChild(oDw);
}

void Mdi::actionAbout_KitchenSink()
{
   AboutCS *oDw = new AboutCS("ks");
   addMdiChild(oDw);
}

void Mdi::actionAbout()
{
   QString textBody = "<font color='#000080'><table style=margin-right:25>"
                      "<tr><td><nobr>Developed by Barbara Geller</nobr></td><td>barbara@copperspice.com</td></tr>"
                      "<tr><td style=padding-right:25><nobr>Developed by Ansel Sermersheim</nobr></td><td>ansel@copperspice.com</td></tr>"
                      "</table></font>"
                      "<br>"
                      "<p><small>Copyright 2012-2017 BG Consulting, All rights reserved.<br>"
                      "This program is provided AS IS with no warranty of any kind.<br></small></p>";

   //
   QMessageBox msgB;
   msgB.setIcon(QMessageBox::NoIcon);
   msgB.setWindowIcon(QIcon("://resources/ks_cs.ico"));

   msgB.setWindowTitle(tr("About Kitchen Sink-Cs5"));
   msgB.setText(tr("<p style=margin-right:25><center><h5>Version: 1.2.1<br>Build # 01.31.2017</h5></center></p>"));
   msgB.setInformativeText(textBody);

   msgB.setStandardButtons(QMessageBox::Ok);
   msgB.setDefaultButton(QMessageBox::Ok);

   msgB.exec();
}
