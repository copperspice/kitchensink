#ifndef FONTPICKER_H
#define FONTPICKER_H

#include "ui_fontpicker.h"

#include <QWidget>

class FontPicker : public QWidget
{
   Q_OBJECT
      
   public:
      explicit FontPicker(QWidget *parent = 0);
      ~FontPicker();
      
   private:
      Ui::FontPicker *ui;

   private slots:
      void setFont();

};

#endif // FONTPICKER_H
