#ifndef STYLE_DW_H
#define STYLE_DW_H

#include "mdi.h"
#include "ui_style_dw.h"
#include "style_edit.h"

class Style_DW : public QMainWindow
{
   Q_OBJECT

   public:
      Style_DW(Mdi *parent);
      ~Style_DW();

   private:     
      Ui::Style_DW *ui;
      Mdi *m_parent;
      Style_Edit *m_style;

   private slots:
      void on_actionAbout_triggered();
      void on_actionEditStyle_triggered();
      void actionButton(QAbstractButton *button);      
      void actionClose();
};

#endif
