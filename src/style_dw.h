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

   protected:
      void closeEvent(QCloseEvent *event) override;

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
