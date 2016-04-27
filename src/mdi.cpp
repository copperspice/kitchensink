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
   : QMainWindow(), ui(new Ui::Mdi)
{
   ui->setupUi(this);
   setWindowTitle(tr("Kitchen Sink-Cs5"));
   setWindowIcon(QIcon("://resources/ks_cs.ico"));

   setUnifiedTitleAndToolBarOnMac(true);
}

Mdi::~Mdi()
{
   delete ui;
}

void Mdi::changeEvent(QEvent *event)
{
   if (event->type() == QEvent::LanguageChange) {
      ui->retranslateUi(this);
   }

   // calls parent, will change the title bar
   QMainWindow::changeEvent(event);
}

void Mdi::addMdiChild(QWidget *oDw)
{
   QMdiSubWindow *subWindow = ui->mdiArea->addSubWindow(oDw);
   subWindow->show();
}

// file
void Mdi::on_actionClose_Window_triggered()
{
   QMdiSubWindow *temp = ui->mdiArea->currentSubWindow();

   if (temp) {
      temp->close();
   }
}

void Mdi::on_actionCloseAll_Windows_triggered()
{
   ui->mdiArea->closeAllSubWindows();
}

void Mdi::on_actionExit_Program_triggered()
{
   close();
}


// samples
void Mdi::on_actionColorPicker_triggered()
{
   ColorPicker *oDw = new ColorPicker();
   addMdiChild(oDw);
}

void Mdi::on_actionFonts_triggered()
{
   FontPicker *oDw = new FontPicker();
   addMdiChild(oDw);
}

void Mdi::on_actionDraw_triggered()
{
   Draw *oDw = new Draw();
   addMdiChild(oDw);
}

void Mdi::on_actionInternational_triggered()
{
   International *oDw = new International();
   addMdiChild(oDw);
}

void Mdi::on_actionSystemTray_triggered()
{
   SysTray *oDw = new SysTray();
   addMdiChild(oDw);
}

void Mdi::on_actionSvgView_triggered()
{
   Svg_View *oDw = new Svg_View();
   addMdiChild(oDw);
}

void Mdi::on_actionStandardDialog_triggered()
{
   Dialogs *oDw = new Dialogs();
   addMdiChild(oDw);
}

void Mdi::on_actionStandardPath_triggered()
{
   StdPath *oDw = new StdPath();
   addMdiChild(oDw);
}

void Mdi::on_actionStyleSheetDialog_triggered()
{
   Style_DW *oDw = new Style_DW(this);
   addMdiChild(oDw);
}

void Mdi::on_actionScript_triggered()
{
   ksMsg("JS Scripts - CsScript is not available");

/*
   Script *oDw = new Script();
   addMdiChild(oDw);
*/
}

void Mdi::on_actionXml_triggered()
{
   Xml *oDw = new Xml();
   addMdiChild(oDw);
}

void Mdi::on_actionXmlPatterns_triggered()
{
    XmlPatterns *oDw = new XmlPatterns();
   addMdiChild(oDw);
}

// audio & visual
void Mdi::on_actionMusicPlayer_triggered()
{ 
   MusicPlayer *oDw = new MusicPlayer();

   if ( oDw->loaded() ) {
      addMdiChild(oDw);
   } else {
      delete oDw;
   }
}

void Mdi::on_actionVideoWidget_triggered()
{
   VideoPlayer *oDw = new VideoPlayer();
   addMdiChild(oDw);
}

void Mdi::on_actionHTML_Viewer_triggered()
{
   Html_Viewer *oDw = new Html_Viewer();
   addMdiChild(oDw);
}

void Mdi::on_actionWebBrowser_triggered()
{   
   WebBrowser *oDw = new WebBrowser(this);
   addMdiChild(oDw);
}


// views
void Mdi::on_actionTableView_triggered()
{
   TableView *oDw = new TableView();
   addMdiChild(oDw);
}

void Mdi::on_actionTreeView_triggered()
{
   TreeView *oDw = new TreeView();
   addMdiChild(oDw);
}

void Mdi::on_actionListView_triggered()
{
   ListView *oDw = new ListView();
   addMdiChild(oDw);
}

void Mdi::on_actionTableWidget_View_triggered()
{
   TableWidget_View *oDw = new TableWidget_View();
   addMdiChild(oDw);
}


// widgets
void Mdi::on_actionCalendar_triggered()
{
   Calendar *oDw = new Calendar();
   addMdiChild(oDw);
}

void Mdi::on_actionLineEdit_triggered()
{
   LineEdit *oDw = new LineEdit();
   addMdiChild(oDw);
}

void Mdi::on_actionSliders_triggered()
{
   Sliders *oDw = new Sliders();
   addMdiChild(oDw);
}

void Mdi::on_actionTabs_triggered()
{
   TabDialog *oDw = new TabDialog();
   addMdiChild(oDw);
}

// graphics
void Mdi::on_actionAnalog_Clock_triggered()
{
   AnalogClock *oDw = new AnalogClock();
   addMdiChild(oDw);
}

void Mdi::on_actionAnimated_Tiles_triggered()
{
   AnimatedTiles *oDw = new AnimatedTiles();
   addMdiChild(oDw);
}

void Mdi::on_actionFridge_Magnets_triggered()
{
   FridgeMagnet *oDw = new FridgeMagnet();
   addMdiChild(oDw);
}

void Mdi::on_actionGrabber_triggered()
{
   Grabber *oDw = new Grabber();
   addMdiChild(oDw);
}

void Mdi::on_actionLighting_triggered()
{
   Lighting *oDw = new Lighting();
   addMdiChild(oDw);
}

void Mdi::on_actionMandelbrot_triggered()
{
   Mandelbrot_Widget *oDw = new Mandelbrot_Widget();
   addMdiChild(oDw);
}

void Mdi::on_actionScreen_Shot_triggered()
{
   Screenshot *oDw = new Screenshot();
   addMdiChild(oDw);
}

void Mdi::on_actionWiggle_Boxes_triggered()
{   
   ksMsg("Wiggle Boxes - CsDeclarative is not available");

/*
   Wiggle_Boxes *oDw = new Wiggle_Boxes();
   addMdiChild(oDw);
*/
}

void Mdi::on_actionWorld_Clock_triggered()
{
   ksMsg("World Clock - CsDeclarative is not available");

/*
   World_Clock *oDw = new World_Clock();
   addMdiChild(oDw);
*/
}

//  help
void Mdi::on_actionAbout_CopperSpice_triggered()
{
   AboutCS *oDw = new AboutCS("cs");
   addMdiChild(oDw);
}

void Mdi::on_actionAbout_KitchenSink_triggered()
{
   AboutCS *oDw = new AboutCS("ks");
   addMdiChild(oDw);
}

void Mdi::on_actionAbout_triggered()
{
   QString textBody = "<font color='#000080'><table style=margin-right:25>"
                      "<tr><td><nobr>Developed by Barbara Geller</nobr></td><td>barbara@copperspice.com</td></tr>"
                      "<tr><td style=padding-right:25><nobr>Developed by Ansel Sermersheim</nobr></td><td>ansel@copperspice.com</td></tr>"
                      "</table></font>"
                      "<br>"
                      "<p><small>Copyright 2012-2016 BG Consulting, All rights reserved.<br>"
                      "This program is provided AS IS with no warranty of any kind.<br></small></p>";

   //
   QMessageBox msgB;
   msgB.setIcon(QMessageBox::NoIcon);
   msgB.setWindowIcon(QIcon("://resources/ks_cs.ico"));

   msgB.setWindowTitle(tr("About Kitchen Sink-Cs5"));
   msgB.setText(tr("<p style=margin-right:25><center><h5>Version: 1.2.1<br>Build # 04.27.2016</h5></center></p>"));
   msgB.setInformativeText(textBody);

   msgB.setStandardButtons(QMessageBox::Ok);
   msgB.setDefaultButton(QMessageBox::Ok);

   msgB.exec();
}
