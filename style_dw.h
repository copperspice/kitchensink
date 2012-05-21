#ifndef STYLE_DW_H
#define STYLE_DW_H

#include "ui_style_dw.h"
#include "style_edit.h"

class Style_DW : public QMainWindow
{
   Q_OBJECT

   public:
      Style_DW();
      ~Style_DW();

   private slots:
      void on_actionAbout_triggered();
      void on_actionEditStyle_triggered();
      void actionButton(QAbstractButton *button);
      void actionClose();

   private:     
      Ui::Style_DW *ui;
};

#endif
