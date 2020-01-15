/**********************************************************************
*
* Copyright (c) 2012-2020 Barbara Geller
* Copyright (c) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
* KitchenSink is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
***********************************************************************/

#ifndef COLORPICKER_H
#define COLORPICKER_H

#include "ui_colorpicker.h"

#include <QWidget>

class ColorPicker : public QWidget
{
   CS_OBJECT(ColorPicker)

   public:
      explicit ColorPicker(QWidget *parent = nullptr);
      ~ColorPicker();

   private:
      Ui::ColorPicker *ui;

      // slot declarations
      void setColor();
      void actionClose();
};

#endif
