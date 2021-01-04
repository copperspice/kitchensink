/***********************************************************************
*
* Copyright (c) 2012-2021 Barbara Geller
* Copyright (c) 2012-2021 Ansel Sermersheim
* Copyright (c) 2015 The Qt Company Ltd.
*
* This file is part of KitchenSink.
*
* KitchenSink is free software, released under the BSD 2-Clause license.
* For license details refer to LICENSE provided with this project.
*
* CopperSpice is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* https://opensource.org/licenses/BSD-2-Clause
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
