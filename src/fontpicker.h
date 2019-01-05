/**********************************************************************
*
* Copyright (c) 2012-2019 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
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

#ifndef FONTPICKER_H
#define FONTPICKER_H

#include "ui_fontpicker.h"

#include <QWidget>

class FontPicker : public QWidget
{
   CS_OBJECT(FontPicker)

   public:
      explicit FontPicker(QWidget *parent = nullptr);
      ~FontPicker();

   private:
      Ui::FontPicker *ui;

      // slot declarations
      void setFont();
      void actionClose();
};

#endif
