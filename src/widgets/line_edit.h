/**********************************************************************
*
* Copyright (c) 2012-2018 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
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
