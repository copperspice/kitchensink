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

#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "ui_line_edit.h"

#include <QWidget>

class LineEdit : public QWidget
{
   CS_OBJECT(LineEdit)

   public:
       LineEdit();
       ~LineEdit();

   private:
       CS_SLOT_1(Private, void alignChanged(int data))
       CS_SLOT_2(alignChanged)

       CS_SLOT_1(Private, void maskChanged(int data))
       CS_SLOT_2(maskChanged)

       CS_SLOT_1(Private, void passwordChanged(int data))
       CS_SLOT_2(passwordChanged)

       CS_SLOT_1(Private, void validChanged(int data))
       CS_SLOT_2(validChanged)

       CS_SLOT_1(Private, void readonlyChanged(int data))
       CS_SLOT_2(readonlyChanged)

       Ui::LineEdit *ui;
};


#endif
