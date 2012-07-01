#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "ui_colorpicker.h"

#include <QWidget>

class ColorPicker : public QWidget
{
   Q_OBJECT
      
   public:
      explicit ColorPicker(QWidget *parent = 0);
      ~ColorPicker();
      
   private:
      Ui::ColorPicker *ui;

   private slots:
      void setColor();
      void actionClose();
};

#endif
