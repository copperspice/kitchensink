#ifndef SCRIPT_H
#define SCRIPT_H

#include "ui_script.h"
#include "mdi.h"

#include <QWidget>
#include <QStandardItemModel>

class Script : public QWidget
{
   Q_OBJECT

   public:
      explicit Script();
      ~Script();

   private:
      Ui::Script *ui;
      QString m_fileName;    
      void displayScript();
      void jsScript(QString contents);

   private slots:
      void actionOpenScript();
      void actionRunScript();
      void actionClose();

};

#endif
