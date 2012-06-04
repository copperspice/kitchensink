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
      void removeMdiChild(QWidget *);

   private:
      Ui::Mdi *ui;
      void changeEvent(QEvent *event);

   private slots:
      void on_actionColorPicker_triggered();
      void on_actionFonts_triggered();
      void on_actionDraw_triggered();
      void on_actionInternational_triggered();
      void on_actionMusicPlayer_triggered();
      void on_actionPieChart_triggered();
      void on_actionSystemTray_triggered();

      void on_actionStandardDialog_triggered();
      void on_actionStyleSheetDialog_triggered();     
      void on_actionHTML_Viewer_triggered();
      void on_actionWebBrowser_triggered();
      void on_actionXml_triggered();

      void on_actionTableView_triggered();
      void on_actionTreeView_triggered();
      void on_actionListView_triggered();
      void on_actionTableWidget_View_triggered();
      void on_actionTableView_Delegate_triggered();

      void on_actionCalendar_triggered();
      void on_actionLineEdit_triggered();      
      void on_actionSliders_triggered();
      void on_actionTabs_triggered();

      void on_actionAbout_CopperSpice_triggered();
      void on_actionAbout_triggered();
      void on_actionExit_Program_triggered();
};

#endif // MDI_H
