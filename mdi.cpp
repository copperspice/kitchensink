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
#include "sliders.h"
#include "style_dw.h"
#include "systray.h"
#include "tabdialog.h"
#include "tableview.h"
#include "tablewidget_view.h"
#include "treeview.h"
#include "web_browser.h"
#include "xml.h"

#include "mdi.h"
#include "ui_mdi.h"

#include <QMdiSubWindow>


Mdi::Mdi()
   : QMainWindow(), ui(new Ui::Mdi)
{
   ui->setupUi(this);
   setWindowTitle(tr("Kitchen Sink - Qt Framework"));
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

void Mdi::removeMdiChild(QWidget *oDw)
{
   // not used as the child can call subWindow->close()
   // ui->mdiArea->closeActiveSubWindow();
}


// file
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

void Mdi::on_actionMusicPlayer_triggered()
{
   MusicPlayer *oDw = new MusicPlayer();
   addMdiChild(oDw);
}

void Mdi::on_actionPieChart_triggered()
{
   //Draw *oDw = new Draw();
   //addMdiChild(oDw);

   ksMsg("Pie Chart sample has not been implemented");
}

void Mdi::on_actionSystemTray_triggered()
{
   SysTray *oDw = new SysTray();
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

void Mdi::on_actionXml_triggered()
{
   Xml *oDw = new Xml();
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

void Mdi::on_actionTableView_Delegate_triggered()
{
   //TableView *oDw = new TableView();
   //addMdiChild(oDw);

   ksMsg("Delegate sample has not been implemented");
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
   QMessageBox::about(this, tr("About Kitchen Sink"),
       tr("<center>Version: 1.0<br/>"
       "(Build: 5/25/2012)<br/><br/>"
       "Developed by Barbara Geller        barbara@2copperspice.com<br/>"
       "Developed by Ansel Sermershemim    ansel@copperspice.comm<br/></center><br/>"));
}
