/**********************************************************************
*
* Copyright (c) 2012-2017 Barbara Geller
* Copyright (C) 2015 The Qt Company Ltd.
*
* You may use this file under the terms of the 2-Clause BSD license
* provided with KitchenSink or available at:
*
* https://opensource.org/licenses/BSD-2-Clause
*
***********************************************************************/

#ifndef STYLE_DW_H
#define STYLE_DW_H

#include "ui_style_dw.h"
#include "style_edit.h"

#include <QMainWindow>

class MainWindow;

class Style_DW : public QMainWindow
{
   CS_OBJECT(Style_DW)

   public:
      Style_DW(MainWindow *parent);
      ~Style_DW();
      void styleEditClose();

   private:
      CS_SLOT_1(Private, void actionAbout())
      CS_SLOT_2(actionAbout)

      CS_SLOT_1(Private, void actionEdit())
      CS_SLOT_2(actionEdit)

      CS_SLOT_1(Private, void actionClose())
      CS_SLOT_2(actionClose)

      Ui::Style_DW *ui;
      MainWindow *m_parent;
      Style_Edit *m_style;
};

#endif
