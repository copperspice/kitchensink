#include "util.h"
#include "aboutcs.h"
#include "calendar.h"
#include "colorpicker.h"
#include "dialogs.h"
#include "draw.h"
#include "fontpicker.h"
#include "html_viewer.h"
#include "musicplayer.h"
#include "translate.h"
#include "line_edit.h"
#include "listview.h"
#include "script.h"
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

#include "mdi.h"
#include "ui_mdi.h"

#include <QMdiSubWindow>


Mdi::Mdi()
   : QMainWindow(), ui(new Ui::Mdi)
{
   ui->setupUi(this);
   setWindowTitle(tr("Kitchen Sink-Cs1"));
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
   Translate *oDw = new Translate();
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

void Mdi::on_actionStyleSheetDialog_triggered()
{
   Style_DW *oDw = new Style_DW(this);
   addMdiChild(oDw);
}

void Mdi::on_actionScript_triggered()
{
   Script *oDw = new Script();
   addMdiChild(oDw);
}

void Mdi::on_actionXml_triggered()
{
   Xml *oDw = new Xml();
   addMdiChild(oDw);
}

void Mdi::on_actionXmlPatterns_triggered()
{
   //Xml *oDw = new Xml();
   //addMdiChild(oDw);

   ksMsg("XML Patterns sample has not been implemented");
}

// audio & visual
void Mdi::on_actionMusicPlayer_triggered()
{
   MusicPlayer *oDw = new MusicPlayer();
   addMdiChild(oDw);
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

//  help
void Mdi::on_actionAbout_CopperSpice_triggered()
{
   AboutCS *oDw = new AboutCS();
   addMdiChild(oDw);
}

void Mdi::on_actionAbout_triggered()
{
   QString textBody = "<font color='#000080'><table style=margin-right:25>"
                      "<tr><td><nobr>Developed by Barbara Geller</nobr></td><td>barbara@copperspice.com</td></tr>"
                      "<tr><td style=padding-right:25><nobr>Developed by Ansel Sermersheim</nobr></td><td>ansel@copperspice.com</td></tr>"
                      "</table></font>"
                      "<br>"
                      "<p><small>Copyright 2012 BG Consulting, All rights reserved.<br>"
                      "This program is provided AS IS with no warranty of any kind.<br></small></p>";

   //
   QMessageBox msgB;
   msgB.setIcon(QMessageBox::NoIcon);
   msgB.setWindowIcon( QIcon("://resources/plus.png"));

   msgB.setWindowTitle(tr("About Kitchen Sink-Cs1"));
   msgB.setText(tr("<p style=margin-right:25><center><h5>Version: 1.0<br>Build # 8.17.2012</h5></center></p>"));
   msgB.setInformativeText(textBody);

   msgB.setStandardButtons(QMessageBox::Ok);
   msgB.setDefaultButton(QMessageBox::Ok);

   msgB.exec();
}
